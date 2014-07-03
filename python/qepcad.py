#!/usr/bin/python3

import os
import re
from subprocess import Popen, DEVNULL, PIPE

import sympy as sp
from sympy.core.add import Add
from sympy.core.mul import Mul
from sympy.core.power import Pow

from sympy.parsing.sympy_parser import parse_expr

# QEPCAD supports the following quantifiers:
	# E = "there exists"
	# A = "for all"
	# F = "for infinitely many"
	# G = "for all but finitely many"
	# C = "for a connected subset"
	# Xk = "for exactly k distinct values"

Exists = sp.Symbol("Exists")
ForAll = sp.Symbol("ForAll")
ForInfinitelyMany = sp.Symbol("ForInfinitelyMany")
ForAllButFinitelyMany = sp.Symbol("ForAllButFinitelyMany")

TRUE = sp.Symbol("TRUE")
FALSE = sp.Symbol("FALSE")

NotEqual = sp.Symbol("NotEqual")
Equal = sp.Symbol("Equal")
StrictLessThan = sp.Symbol("StrictLessThan")
LessThan = sp.Symbol("LessThan")
StrictGreaterThan = sp.Symbol("StrictGreaterThan")
GreaterThan = sp.Symbol("GreaterThan")

global_qepcad_path = None

def find_qepcad_path():
	global global_qepcad_path
	if global_qepcad_path is not None:
		return global_qepcad_path

	directories = [".", "..", os.path.join("..", "..")]

	qepcad_name = "qepcad"
	if os.name == 'nt':
		qepcad_name = "qepcad.exe"

	for start_dir in directories:
		for root, dirs, files in os.walk(start_dir):
			if qepcad_name in files:
				global_qepcad_path = os.path.abspath(root)
				print("Found qepcad at", global_qepcad_path)
				return global_qepcad_path

	return None

# def trim_extra_brackets(strarg):
# 	count = 0
# 	count_is_zero = False
# 	for ch in strarg:
# 		if ch == '(':
# 			count += 1
# 		if ch == ')':
# 			count -= 1
# 		assert(count >= 0)
# 		if count == 0:
# 			count_is_zero = True
# 	if count_is_zero:
# 		strarg = strarg[1:-1]
# 	return strarg

def sympy_to_qepcad_string(expr):
	func = expr.func
	# if func is not None:
	# 	print("func =", func)

	args = expr.args
	strargs = [sympy_to_qepcad_string(x) for x in args]

	if func is Add:
		return "(" + " + ".join(strargs) + ")"
	elif func is Mul:
		return "(" + " ".join(strargs) + ")"
	elif func is Pow:
		return "(" + "^".join(strargs) + ")"

	elif func is sp.Eq or str(func) == "Equal":
		return "[" + strargs[0] + " = " + strargs[1] + "]"
	elif func is sp.Ne or str(func) == "NotEqual":
		return "[" + strargs[0] + " /= " + strargs[1] + "]"
	elif func is sp.GreaterThan or str(func) == "GreaterThan":
		return "[" + strargs[0] + " >= " + strargs[1] + "]"
	elif func is sp.StrictGreaterThan or str(func) == "StrictGreaterThan":
		return "[" + strargs[0] + " > " + strargs[1] + "]"
	elif func is sp.LessThan or str(func) == "LessThan":
		return "[" + strargs[0] + " <= " + strargs[1] + "]"
	elif func is sp.StrictLessThan or str(func) == "StrictLessThan":
		return "[" + strargs[0] + " < " + strargs[1] + "]"

	elif func is sp.Or:
		return "[" + strargs[0] + " \/ " + strargs[1] + "]"
	elif func is sp.And:
		return "[" + strargs[0] + " /\ " + strargs[1] + "]"
	elif func is sp.Implies:
		return "[" + strargs[0] + " ==> " + strargs[1] + "]"
	elif func is sp.Equivalent:
		return "[" + strargs[0] + " ==> " + strargs[1] + "]"
	elif func is sp.Not:
		return "~[" + strargs[0] + "]"

	elif str(func) == "Exists":
		return "(E " + strargs[0] + ")" + strargs[1] + ""
	elif str(func) == "ForAll":
		return "(A " + strargs[0] + ")" + strargs[1] + ""
	elif str(func) == "ForInfinitelyMany":
		return "(F " + strargs[0] + ")" + strargs[1] + ""
	elif str(func) == "ForAllButFinitelyMany":
		return "(G " + strargs[0] + ")" + strargs[1] + ""

	else:
		variable_string = str(expr)
		if not len(variable_string) == 1 and not variable_string.isdigit():
			print("\nPARSE ERROR:", variable_string, "\n")
		assert(len(variable_string) == 1 or variable_string.isdigit())
		return variable_string


def run_qepcad(expr, free_vars, non_free_vars):
	working_dir = find_qepcad_path()
	qepcad_path = os.path.join(working_dir, "qepcad")

	# 	input = """[Petter Strandmarks test 1]
	# (a,b,x)
	# 2
	# (Ex)[x^2 + a x + b = 0].
	# finish
	# """

	input = """[Petter Strandmarks test 1]\n"""
	input += "(" + ",".join([str(x) for x in free_vars + non_free_vars]) + ")\n"
	input += str(len(free_vars)) + "\n"
	input += sympy_to_qepcad_string(expr) + ".\n"
	input += "finish\n"

	process = Popen(qepcad_path,
	                stdout=PIPE,
	                stdin=PIPE,
	                cwd=working_dir,
	                universal_newlines=True)

	stdout, stderr = process.communicate(input)

	if stderr is not None:
		print(stderr)

	if "error" in stdout.lower():
		print("")
		print("Error detected. Sent the input:")
		print(input)
		print("")
		print("Got output:")
		print(stdout)
		return None

	before = "An equivalent quantifier-free formula:"
	after  = "=====================  The End  ======================="
	output_string = stdout[stdout.find(before) + len(before) : stdout.find(after)]
	output_string = output_string.strip(" \n\t")

	# Fix multiplication: "4 a" -> "4 * a".
	new_output_string = None
	while output_string != new_output_string:
		new_output_string = output_string
		output_string = re.sub(r'([a-z0-9])\s([a-z0-9])', r'\1 * \2', output_string)

	# Fix power.
	output_string = output_string.replace("^", "**")
	try:
		parsed_output = parse_expr(output_string)
	except:
		print("Error parsing", output_string)
		return None

	return parsed_output
