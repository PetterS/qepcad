#!/usr/bin/python3

import re
from subprocess import Popen, DEVNULL, PIPE
import unittest

import sympy as sp

import qepcad
from qepcad import run_qepcad, TRUE, FALSE
from qepcad import Exists, ForAll, ForInfinitelyMany, ForAllButFinitelyMany
from qepcad import NotEqual, Equal, StrictLessThan, LessThan, StrictGreaterThan, GreaterThan

x = sp.Symbol('x')
y = sp.Symbol('y')
z = sp.Symbol('z')
a = sp.Symbol('a')
b = sp.Symbol('b')
c = sp.Symbol('c')
d = sp.Symbol('d')

class TestQuantifiers(unittest.TestCase):
	def test_forall(self):
		expr = ForAll(x, x >= 22)
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

	def test_exists(self):
		expr = Exists(x, x >= 22)
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

	def test_multiple_exists(self):
		expr = Exists(x, Exists(y, x >= 22))
		out = run_qepcad(expr, [], [x, y])
		self.assertEqual(out, TRUE)

	def test_forall_exists(self):
		expr = ForAll(x, Exists(y, sp.Eq(x, 2 * y)))
		out = run_qepcad(expr, [], [x, y])
		self.assertEqual(out, TRUE)

	def test_forall_does_not_exist(self):
		expr = ForAll(x, Exists(y, sp.Eq(x, y**2)))
		out = run_qepcad(expr, [], [x, y])
		self.assertEqual(out, FALSE)

	def test_for_infinitely_many(self):
		expr = ForInfinitelyMany(x, x >= 22)
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

		expr = ForInfinitelyMany(x, sp.Eq(x, 22))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

		expr = Exists(x, sp.Eq(x, 22))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

	def test_for_all_but_finitely_many(self):
		expr = ForAllButFinitelyMany(x,
		       ForAll(y,
		       Exists(z, sp.Eq(y, z * x))))
		out = run_qepcad(expr, [], [x, y, z])
		self.assertEqual(out, TRUE)

		expr = ForAll(x,
		       ForAll(y,
		       Exists(z, sp.Eq(y, z * x))))
		out = run_qepcad(expr, [], [x, y, z])
		self.assertEqual(out, FALSE)

class TestRelationalOperators(unittest.TestCase):

	def test_not_equal(self):
		expr = ForAll(x, NotEqual(x, x + 1))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

		expr = ForAll(x, NotEqual(x, 2 * x))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

	def test_equal(self):
		expr = Exists(x, qepcad.Equal(x, x + 1))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

		expr = Exists(x, qepcad.Equal(x, 2 * x))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

	def test_less(self):
		expr = Exists(x, StrictLessThan(x + 1, x))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

		# Sympy simplifies simple expressions. Make it a bit
		# more complicated to test "<"
		expr = Exists(x, Exists(y, sp.And(x + 1 < y, sp.Eq(x, y))))
		out = run_qepcad(expr, [], [x, y])
		self.assertEqual(out, FALSE)

class TestLogicalOperators(unittest.TestCase):

	def test_or(self):
		expr = ForAll(x, sp.Or(x >= 22, x < 22))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

	def test_and(self):
		expr = ForAll(x, sp.And(x >= 5, x < 1))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

	def test_implies(self):
		expr = ForAll(x, sp.Implies(x > 0, x >= 0))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

		expr = ForAll(x, sp.Implies(x > 0, x < 0))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, FALSE)

	def test_equivalent(self):
		expr = ForAll(x, sp.Equivalent(x >= 0, x**3 >= 0))
		out = run_qepcad(expr, [], [x])
		self.assertEqual(out, TRUE)

	# def test_not(self):
	# 	expr = ForAll(x, sp.Or(x, sp.Not(x)))
	# 	out = run_qepcad(expr, [], [x])
	# 	self.assertEqual(out, TRUE)

class TestQuadratic(unittest.TestCase):

	def test_a_b(self):
		expr = Exists(x, sp.Eq(x**2 + a*x + b, 0))
		out = run_qepcad(expr, [a, b], [x])

		# We expect 4b - a^2 <= 0
		self.assertFalse(out.subs(b,1).subs(a,1))
		self.assertTrue(out.subs(b,1).subs(a,100))
		self.assertTrue(out.subs(b,100).subs(a,100))
		self.assertFalse(out.subs(b,100).subs(a,1))


if __name__ == '__main__':
	unittest.main()
