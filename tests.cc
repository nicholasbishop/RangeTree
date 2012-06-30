/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "range_tree.hh"

typedef RangeTree<unsigned> RT;

static void test_initialization_0() {
	RT rt(UINT_MAX);

	assert(rt.size() == 1);
	assert(rt.has_range(0, UINT_MAX));
}

static void test_take_any_0() {
	RT rt(UINT_MAX);

	rt.take_any();
	assert(rt.size() == 1);
	assert(rt.has_range(1, UINT_MAX));
}

static void test_take_any_1() {
	RT rt(10);

	for (unsigned i = 0; i < 10; i++) {
		rt.take_any();
		assert(rt.size() == 1);
		assert(rt.has_range(i + 1, 10));
	}
}

static void test_take_0() {
	RT rt(10);

	rt.take(0);
	assert(rt.size() == 1);
	assert(rt.has_range(1, 10));

	rt.take(10);
	assert(rt.size() == 1);
	assert(rt.has_range(1, 9));

	rt.take(2);
	assert(rt.size() == 2);
	assert(rt.has_range(1, 1));
	assert(rt.has_range(3, 9));

	rt.take(6);
	assert(rt.size() == 3);
	assert(rt.has_range(1, 1));
	assert(rt.has_range(3, 5));
	assert(rt.has_range(7, 9));

	rt.take(1);
	assert(rt.size() == 2);
	assert(rt.has_range(3, 5));
	assert(rt.has_range(7, 9));

	rt.take(8);
	assert(rt.size() == 3);
	assert(rt.has_range(3, 5));
	assert(rt.has_range(7, 7));
	assert(rt.has_range(9, 9));

	rt.take(7);	
	rt.take(9);
	assert(rt.size() == 1);
	assert(rt.has_range(3, 5));

	rt.take(3);	
	assert(rt.size() == 1);
	assert(rt.has_range(4, 5));

	rt.take(5);	
	assert(rt.size() == 1);
	assert(rt.has_range(4, 4));

	rt.take(4);	
	assert(rt.empty());
}

/* Take and release from the middle */
static void test_release_0() {
	RT rt(10);

	rt.take(5);
	assert(rt.size() == 2);
	assert(rt.has_range(0, 4));
	assert(rt.has_range(6, 10));
	rt.release(5);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 10));
}

/* Take and release from the beginning */
static void test_release_1() {
	RT rt(10);

	rt.take(0);
	assert(rt.size() == 1);
	assert(rt.has_range(1, 10));
	rt.release(0);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 10));

	rt = RT(UINT_MAX);

	rt.take(0);
	assert(rt.size() == 1);
	assert(rt.has_range(1, UINT_MAX));
	rt.release(0);
	assert(rt.size() == 1);
	assert(rt.has_range(0, UINT_MAX));
}

/* Take and release multiple from the beginning */
static void test_release_2() {
	RT rt(10);

	rt.take(0);
	rt.take(1);
	assert(rt.size() == 1);
	assert(rt.has_range(2, 10));

	rt.release(0);
	assert(rt.size() == 2);
	assert(rt.has_range(0, 0));
	assert(rt.has_range(2, 10));

	rt.release(1);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 10));
}

/* Take and release from the end */
static void test_release_3() {
	RT rt(10);

	rt.take(10);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 9));
	rt.release(10);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 10));
}

/* Take and release multiple from the end */
static void test_release_4() {
	RT rt(10);

	rt.take(9);
	rt.take(10);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 8));

	rt.release(10);
	assert(rt.size() == 2);
	assert(rt.has_range(0, 8));
	assert(rt.has_range(10, 10));

	rt.release(9);
	assert(rt.size() == 1);
	assert(rt.has_range(0, 10));
}

/* Take and release multiple from middle */
static void test_release_5() {
	RT rt(10);

	rt.take(4);
	rt.take(5);
	rt.take(6);
	assert(rt.size() == 2);
	assert(rt.has_range(0, 3));
	assert(rt.has_range(7, 10));

	rt.release(4);
	assert(rt.size() == 2);
	assert(rt.has_range(0, 4));
	assert(rt.has_range(7, 10));
}

/* Take and release multiple from middle */
static void test_release_6() {
	RT rt(10);

	rt.take(4);
	rt.take(5);
	rt.take(6);
	assert(rt.size() == 2);
	assert(rt.has_range(0, 3));
	assert(rt.has_range(7, 10));

	rt.release(5);
	assert(rt.size() == 3);
	assert(rt.has_range(0, 3));
	assert(rt.has_range(5, 5));
	assert(rt.has_range(7, 10));
}

int main()
{
	test_initialization_0();
	test_take_any_0();
	test_take_any_1();
	test_take_0();
	test_release_0();
	test_release_1();
	test_release_2();
	test_release_3();
	test_release_4();
	test_release_5();
	test_release_6();

	return 0;
}
