#include "unity.h"
#include "history_buffer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_HistoryBufferNew_given_6_should_allocate_HistoryBuffer_object_with_a_buffer_of_6(void)
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	TEST_ASSERT_NOT_NULL(hb);
	TEST_ASSERT_NOT_NULL(hb->buffer);
	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(0, hb->size);
	TEST_ASSERT_EQUAL_PTR(hb->buffer,hb->initial);
	historyBufferDel(hb);
}


void test_historyBufferAdd_given_123_should_get_both_initial_latest_and_end_equal_to_abc()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char string1[] = "123";
	
	historyBufferAdd(hb, string1);

	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(1, hb->size);
	TEST_ASSERT_EQUAL_STRING("123", hb->initial);
	TEST_ASSERT_EQUAL_STRING("123", hb->latest);
    historyBufferDel(hb);

}


void test_historyBufferAdd_given_123_and_abc_should_get_initial_is_123_and_latest_equal_to_abc()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char string1[] = "123";
	char string2[] = "abc";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);

	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(2, hb->size);
	TEST_ASSERT_EQUAL_STRING("123", hb->initial);
	TEST_ASSERT_EQUAL_STRING("abc", hb->latest);
	TEST_ASSERT_EQUAL_STRING("abc", hb->initial += sizeof(String));
    historyBufferDel(hb);
}


void test_historyBufferAdd_given_123_abc_456_789_should_get_initial_is_123_and_latest_is_789()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char string1[] = "123";
	char string2[] = "abc";
	char string3[] = "456";
	char string4[] = "789";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);

	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(4, hb->size);
	TEST_ASSERT_EQUAL_STRING("123", hb->initial);
	TEST_ASSERT_EQUAL_STRING("789", hb->latest);
	TEST_ASSERT_EQUAL_STRING("123", hb->initial);
	TEST_ASSERT_EQUAL_STRING("abc", (hb->initial + sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("456", (hb->initial + 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("789", (hb->initial + 3*sizeof(String)));
    historyBufferDel(hb);
}


void test_historyBufferAdd_given_123_abc_456_789_22_should_get_initial_and_latest_are_22_and_end_is_abc()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char string1[] = "123";
	char string2[] = "abc";
	char string3[] = "456";
	char string4[] = "789";
	char string5[] = "22";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);
	historyBufferAdd(hb, string5);

	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(1, hb->size);
	TEST_ASSERT_EQUAL_STRING("22", hb->initial);
	TEST_ASSERT_EQUAL_STRING("22", hb->latest);
	TEST_ASSERT_EQUAL_STRING("abc", hb->end);
	TEST_ASSERT_EQUAL_STRING("abc", (hb->initial + sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("456", (hb->initial + 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("789", (hb->initial + 3*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("789", hb->buffer);
	TEST_ASSERT_EQUAL_STRING("456", (hb->buffer - sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("abc", (hb->buffer - 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("22", (hb->buffer - 3*sizeof(String)));

    historyBufferDel(hb);
}



void test_historyBufferAdd_given_1_2_3_4_22_33_55_should_get_initial_is_1_latest_is_22_and_end_is_3()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "22";
	char string6[] = "33";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);
	historyBufferAdd(hb, string5);
	historyBufferAdd(hb, string6);


	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(2, hb->size);
	TEST_ASSERT_EQUAL_STRING("22", hb->initial);
	TEST_ASSERT_EQUAL_STRING("33", hb->latest);
	TEST_ASSERT_EQUAL_STRING("3", hb->end);
	TEST_ASSERT_EQUAL_STRING("33", (hb->initial + sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("3", (hb->initial + 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("4", (hb->initial + 3*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("4", hb->buffer);
	TEST_ASSERT_EQUAL_STRING("3", (hb->buffer - sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("33", (hb->buffer - 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("22", (hb->buffer - 3*sizeof(String)));

    historyBufferDel(hb);
}


void test_historyBufferAdd_given_1_2_3_4_22_33_55_66_abc_should_get_initial_is_22_latest_is_abc_and_end_is_22()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "22";
	char string6[] = "33";
	char string7[] = "55";
	char string8[] = "abc";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);
	historyBufferAdd(hb, string5);
	historyBufferAdd(hb, string6);
	historyBufferAdd(hb, string7);
	historyBufferAdd(hb, string8);


	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(4, hb->size);
	TEST_ASSERT_EQUAL_STRING("22", hb->initial);
	TEST_ASSERT_EQUAL_STRING("abc", hb->latest);
	TEST_ASSERT_EQUAL_STRING("22", hb->end);
	TEST_ASSERT_EQUAL_STRING("33", (hb->initial + sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("55", (hb->initial + 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("abc", (hb->initial + 3*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("abc", hb->buffer);
	TEST_ASSERT_EQUAL_STRING("55", (hb->buffer - sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("33", (hb->buffer - 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("22", (hb->buffer - 3*sizeof(String)));

    historyBufferDel(hb);
}


void test_historyBufferAdd_given_1_2_3_4_22_33_55_66_abc_xyz_1plus3_should_get_initial_is_xyz_latest_is_1plus3_and_end_is_55()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "22";
	char string6[] = "33";
	char string7[] = "55";
	char string8[] = "abc";
	char string9[] = "xyz";
	char string10[] = "1+3";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);
	historyBufferAdd(hb, string5);
	historyBufferAdd(hb, string6);
	historyBufferAdd(hb, string7);
	historyBufferAdd(hb, string8);
	historyBufferAdd(hb, string9);
	historyBufferAdd(hb, string10);

	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(2, hb->size);
	TEST_ASSERT_EQUAL_STRING("xyz", hb->initial);
	TEST_ASSERT_EQUAL_STRING("1+3", hb->latest);
	TEST_ASSERT_EQUAL_STRING("55", hb->end);
	TEST_ASSERT_EQUAL_STRING("1+3", (hb->initial + sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("55", (hb->initial + 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("abc", (hb->initial + 3*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("abc", hb->buffer);
	TEST_ASSERT_EQUAL_STRING("55", (hb->buffer - sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("1+3", (hb->buffer - 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("xyz", (hb->buffer - 3*sizeof(String)));

    historyBufferDel(hb);
}



void test_historyBufferAdd_given_1_2_3_4_22_33_55_66_abc_xyz_1plus3_2minus2_3times8_18_19_0_should_get_initial_is_18_latest_is_0_and_end_is_3times8()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "22";
	char string6[] = "33";
	char string7[] = "55";
	char string8[] = "abc";
	char string9[] = "xyz";
	char string10[] = "1+3";
	char string11[] = "2-2";
	char string12[] = "3*8";
	char string13[] = "18";
	char string14[] = "19";
	char string15[] = "0";
	
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);
	historyBufferAdd(hb, string5);
	historyBufferAdd(hb, string6);
	historyBufferAdd(hb, string7);
	historyBufferAdd(hb, string8);
	historyBufferAdd(hb, string9);
	historyBufferAdd(hb, string10);
	historyBufferAdd(hb, string11);
	historyBufferAdd(hb, string12);
	historyBufferAdd(hb, string13);
	historyBufferAdd(hb, string14);
	historyBufferAdd(hb, string15);

	TEST_ASSERT_EQUAL(LENGTH_OF_BUFFER, hb->length);
	TEST_ASSERT_EQUAL(3, hb->size);
	TEST_ASSERT_EQUAL_STRING("18", hb->initial);
	TEST_ASSERT_EQUAL_STRING("0", hb->latest);
	TEST_ASSERT_EQUAL_STRING("3*8", hb->end);
	TEST_ASSERT_EQUAL_STRING("19", (hb->initial + sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("0", (hb->initial + 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("3*8", (hb->initial + 3*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("3*8", hb->buffer);
	TEST_ASSERT_EQUAL_STRING("0", (hb->buffer - sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("19", (hb->buffer - 2*sizeof(String)));
	TEST_ASSERT_EQUAL_STRING("18", (hb->buffer - 3*sizeof(String)));

    historyBufferDel(hb);
}
