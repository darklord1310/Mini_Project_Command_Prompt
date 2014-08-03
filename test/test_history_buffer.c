#include "unity.h"
#include "history_buffer.h"
#include "CException.h"

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



void test_historyBufferReadPrevious_given_1plus6_should_return_1plus6_when_read_once()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char string[] = "1+6";
	
	Try{
	
		historyBufferAdd(hb, string);
		char *string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string , string_return);

	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}




void test_historyBufferReadPrevious_1plus6_2plus8_given_should_return_2plus8_1plus6_when_read_twice()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char string1[] = "1+6";
	char string2[] = "2+8";
	char *string_return;
	
	Try{
		
		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string2 , string_return);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string1 , string_return);

	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}




void test_historyBufferReadPrevious_given_1plus6_2plus8_3plus4_and_size_is_3_should_return_3plus4_2plus8_1plus6_when_read_thrice()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(3);

	char string1[] = "1+6";
	char string2[] = "2+8";
	char string3[] = "3+4";
	char *string_return;
	
	Try{
		
		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string3 , string_return);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string2 , string_return);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string1, string_return);
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}



void test_historyBufferReadPrevious_given_1plus6_2plus8_3plus4_and_size_is_3_should_return_error_when_read_four_times()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(3);

	char string1[] = "1+6";
	char string2[] = "2+8";
	char string3[] = "3+4";
	char *string_return;
	
	Try{
		
		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		string_return = historyBufferReadPrevious(hb);		//1
		TEST_ASSERT_EQUAL_STRING(string3 , string_return);
		string_return = historyBufferReadPrevious(hb);		//2
		TEST_ASSERT_EQUAL_STRING(string2 , string_return);
		string_return = historyBufferReadPrevious(hb);		//3
		TEST_ASSERT_EQUAL_STRING(string1 , string_return);
		string_return = historyBufferReadPrevious(hb);		//4
		TEST_FAIL_MESSAGE("Expect error to be generated");
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		printf("Error generated : NO_MORE_PREVIOUS");
	}
}




void test_historyBufferReadPrevious_given_1_2_3_4_5_when_size_is_4_and_read_5_times_should_get_error()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "5";
	char *string_return;
	
	Try{
	
		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		historyBufferAdd(hb, string5);
		string_return = historyBufferReadPrevious(hb);		//1
		TEST_ASSERT_EQUAL_STRING(string5 , string_return);
		string_return = historyBufferReadPrevious(hb);		//2
		TEST_ASSERT_EQUAL_STRING(string4 , string_return);
		string_return = historyBufferReadPrevious(hb);		//3
		TEST_ASSERT_EQUAL_STRING(string3 , string_return);
		string_return = historyBufferReadPrevious(hb);		//4
		TEST_ASSERT_EQUAL_STRING(string2 , string_return);
		string_return = historyBufferReadPrevious(hb);		//5
		TEST_FAIL_MESSAGE("Expect error to be generated");
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		printf("Error generated : NO_MORE_PREVIOUS");
	}
}




void test_historyBufferReadPrevious_given_1_2_3_4_5_6_7_8_when_size_is_4_and_read_5_times_should_get_error()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "5";
	char string6[] = "6";
	char string7[] = "7";
	char string8[] = "8";
	char *string_return;
	
	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		historyBufferAdd(hb, string5);
		historyBufferAdd(hb, string6);
		historyBufferAdd(hb, string7);
		historyBufferAdd(hb, string8);
		string_return = historyBufferReadPrevious(hb);		//1
		TEST_ASSERT_EQUAL_STRING(string8 , string_return);
		string_return = historyBufferReadPrevious(hb);		//2
		TEST_ASSERT_EQUAL_STRING(string7 , string_return);
		string_return = historyBufferReadPrevious(hb);		//3
		TEST_ASSERT_EQUAL_STRING(string6 , string_return);
		string_return = historyBufferReadPrevious(hb);		//4
		TEST_ASSERT_EQUAL_STRING(string5 , string_return);
		string_return = historyBufferReadPrevious(hb);		//5
		TEST_FAIL_MESSAGE("Expect error to be generated");
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		printf("Error generated : NO_MORE_PREVIOUS");
	}
}




void test_historyBufferReadPrevious_given_1_2_3_4_5_6_7_8_when_size_is_4_and_read_4_times_should_get_8_7_6_5()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "5";
	char string6[] = "6";
	char string7[] = "7";
	char string8[] = "8";
	char *string_return;
	
	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		historyBufferAdd(hb, string5);
		historyBufferAdd(hb, string6);
		historyBufferAdd(hb, string7);
		historyBufferAdd(hb, string8);
		string_return = historyBufferReadPrevious(hb);		//1
		TEST_ASSERT_EQUAL_STRING(string8 , string_return);
		string_return = historyBufferReadPrevious(hb);		//2
		TEST_ASSERT_EQUAL_STRING(string7 , string_return);
		string_return = historyBufferReadPrevious(hb);		//3
		TEST_ASSERT_EQUAL_STRING(string6 , string_return);
		string_return = historyBufferReadPrevious(hb);		//4
		TEST_ASSERT_EQUAL_STRING(string5 , string_return);
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}




void test_historyBufferReadPrevious_given_empty_buffer_should_throw_error()
{

	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(3);
	char *string_return;

	Try{
		string_return = historyBufferReadPrevious(hb);
		TEST_FAIL_MESSAGE("Expect error to be generated");
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		printf("Error generated : NO_MORE_PREVIOUS");
	}
}


void test_historyBufferReadPrevious_given_1_2_when_read_previous_thrice_should_throw_error()
{

	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(2);
	char *string_return;
	char string1[] = "1";
	char string2[] = "2";

	Try{
	
		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		TEST_FAIL_MESSAGE("Expect error to be generated");
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_PREVIOUS,err);
		printf("Error generated : NO_MORE_PREVIOUS");
	}
}


void test_historyBufferReadNext_given_empty_buffer_should_throw_error()
{

	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(3);
	char *string_return;

	Try{

		string_return = historyBufferReadNext(hb);
		TEST_FAIL_MESSAGE("Expect error to be generated");
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		printf("Error generated : NO_MORE_NEXT");
	}
}


void test_historyBufferReadNext_given_read_is_NULL_should_throw_error()
{

	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(3);
	char *string_return;
	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	
	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		string_return = historyBufferReadNext(hb);
		TEST_FAIL_MESSAGE("Expect error to be generated");
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		printf("Error generated : NO_MORE_NEXT");
	}
}



void test_historyBufferReadNext_given_read_is_latest_and_loop_is_0_should_throw_error()
{

	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);
	char *string_return;
	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	
	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadNext(hb);
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}




void test_historyBufferReadNext_given_read_is_latest_and_loop_is_1_should_throw_error()
{

	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);
	char *string_return;
	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "5";
	
	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		historyBufferAdd(hb, string5);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadNext(hb);
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}





void test_historyBufferReadNext_call_twice_given_1_2_3_when_read_point_at_1_should_return_3()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char *string_return;

	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		string_return = historyBufferReadPrevious(hb);	
		string_return = historyBufferReadPrevious(hb);	
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string2 , string_return);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string3 , string_return);
		string_return = historyBufferReadPrevious(hb);
	
	
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}






void test_historyBufferReadNext_call_once_given_1_2_3_4_when_read_point_at_3_should_get_4()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(3);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char *string_return;

	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string4 , string_return);
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}



void test_historyBufferReadNext_call_thrice_given_1_2_3_4_5_6_7_when_read_point_at_4_should_get_5_6_7()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(4);

	char string1[] = "1";
	char string2[] = "2";
	char string3[] = "3";
	char string4[] = "4";
	char string5[] = "5";
	char string6[] = "6";
	char string7[] = "7";
	char *string_return;

	Try{

		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		historyBufferAdd(hb, string5);
		historyBufferAdd(hb, string6);
		historyBufferAdd(hb, string7);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string5 , string_return);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string6 , string_return);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string7 , string_return);
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}





/*  Given input string of 1+2	2+4	  3+6	4+8	  5+10  11-4   12*3 	and the size of buffer is 5 
 *	latest should be pointed to 12*3	after adding all the strings into historybuffer
 *	Read previous 3 times should get 5+10
 *	Read next 2 times should get 12*3
 *	Read previous one time should get 11-4
 *	Read next one time should get 12*3
 *	Read previous 4 times should get 3+6
 *	Read next 2 times should get 5+10
 */
void test_historyBufferReadNext_and_historyBufferReadPrevious()
{
	CEXCEPTION_T err;
	
	HistoryBuffer *hb = historyBufferNew(5);

	char string1[] = "1+2";
	char string2[] = "2+4";
	char string3[] = "3+6";
	char string4[] = "4+8";
	char string5[] = "5+10";
	char string6[] = "11-4";
	char string7[] = "12*3";
	char *string_return;
	
	Try{

		//add 7 times expect hb->latest to be 12*3
		historyBufferAdd(hb, string1);
		historyBufferAdd(hb, string2);
		historyBufferAdd(hb, string3);
		historyBufferAdd(hb, string4);
		historyBufferAdd(hb, string5);
		historyBufferAdd(hb, string6);
		historyBufferAdd(hb, string7);
		TEST_ASSERT_EQUAL_STRING(string7 , hb->latest);
		
		
		//read previous 3 times expect 5+10
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string5 , string_return);
		
		
		//read next 2 times expect 12*3
		string_return = historyBufferReadNext(hb);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string7 , string_return);
		
		//read previous one time expect 11-4
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string6 , string_return);
		
		//read next one time expect 12*3
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string7 , string_return);
		
		//read previous 4 times expect 3+6
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		string_return = historyBufferReadPrevious(hb);
		TEST_ASSERT_EQUAL_STRING(string3 , string_return);
		
		//read next 2 times expect	5+10
		string_return = historyBufferReadNext(hb);
		string_return = historyBufferReadNext(hb);
		TEST_ASSERT_EQUAL_STRING(string5 , string_return);
	
		
	}Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_NO_MORE_NEXT,err);
		TEST_FAIL_MESSAGE("Do not expect error to be generated");
	}
}
