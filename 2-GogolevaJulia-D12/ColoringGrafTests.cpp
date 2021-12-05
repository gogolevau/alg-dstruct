#include <gtest/gtest.h>

extern "C"{
	#include <stdio.h>
	#include "Graf.h"
}

#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

#define ANSWER_LINE_LEN 100


TEST(Example_test, first_example){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 3\n" \
					"2 3\n" \
					"1 3\n" \
					"1 2\n");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 3") == 0);
}

TEST(Simple_test, single_graf_with_zero_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "1 0\n");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Simple_test, single_graf_with_nonzero_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "1 1\n");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1") == 0);
}

TEST(Simple_test, graf_with_two_nodes_and_no_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "2 0\n" \
					"1 2\n");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Simple_test, graf_with_two_nodes_and_one_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "2 0\n" \
					"1 2\n");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Simple_test, graf_with_two_nodes_and_two_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "2 2\n" \
					"1 2\n");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2") == 0);
}

TEST(Line_graf_test, graf_with_three_nodes_and_no_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 0\n" \
					"1 2\n" \
					"2 3");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Line_graf_test, graf_with_three_nodes_and_one_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 1\n" \
					"1 2\n" \
					"2 3");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Line_graf_test, graf_with_three_nodes_and_two_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 2\n" \
					"1 2\n" \
					"2 3");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 1") == 0);
}

TEST(Line_graf_test, graf_with_three_nodes_and_three_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 3\n" \
					"1 2\n" \
					"2 3");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 1") == 0);
}

TEST(Looped_graf_test, graf_with_three_nodes_and_no_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 0\n" \
					"1 2\n" \
					"2 3\n" \
					"3 1");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Looped_graf_test, graf_with_three_nodes_and_one_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 1\n" \
					"1 2\n" \
					"2 3\n" \
					"3 1");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Looped_graf_test, graf_with_three_nodes_and_two_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 2\n" \
					"1 2\n" \
					"2 3\n" \
					"3 1");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Looped_graf_test, graf_with_three_nodes_and_three_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "3 3\n" \
					"1 2\n" \
					"2 3\n" \
					"3 1");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 3") == 0);
}

TEST(Hard_graf_test, graf_with_loop_and_line_and_no_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "6 0\n"
					"1 2\n"
					"1 3\n"
					"2 4\n"
					"3 4\n"
					"3 6\n"
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Hard_graf_test, graf_with_loop_and_line_and_one_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "6 1\n"
					"1 2\n"
					"1 3\n"
					"2 4\n"
					"3 4\n"
					"3 6\n"
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Hard_graf_test, graf_with_loop_and_line_and_two_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "6 2\n"
					"1 2\n"
					"1 3\n"
					"2 4\n"
					"3 4\n"
					"3 6\n"
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 2 1 2 1") == 0);
}

TEST(Hard_graf_test, graf_with_loop_and_line_and_three_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "6 3\n"
					"1 2\n"
					"1 3\n"
					"2 4\n"
					"3 4\n"
					"3 6\n"
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 2 1 2 1") == 0);
}


TEST(Hard_graf_test, graf_with_multy_loop_and_no_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "5 0\n" \
					"1 2\n" \
					"1 5\n" \
					"2 3\n" \
					"2 5\n" \
					"4 3\n" \
					"5 3\n" \
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Hard_graf_test, graf_with_multy_loop_and_one_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input,"5 1\n" \
					"1 2\n" \
					"1 5\n" \
					"2 3\n" \
					"2 5\n" \
					"4 3\n" \
					"5 3\n" \
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Hard_graf_test, graf_with_multy_loop_and_two_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "5 2\n" \
					"1 2\n" \
					"1 5\n" \
					"2 3\n" \
					"2 5\n" \
					"4 3\n" \
					"5 3\n" \
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "0") == 0);
}

TEST(Hard_graf_test, graf_with_multy_loop_and_three_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "5 3\n" \
					"1 2\n" \
					"1 5\n" \
					"2 3\n" \
					"2 5\n" \
					"4 3\n" \
					"5 3\n" \
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 1 2 3") == 0);
}

TEST(Hard_graf_test, graf_with_multy_loop_and_four_color){
	FILE* input = fopen(INPUT_FILENAME, "w");
	fprintf(input, "5 4\n" \
					"1 2\n" \
					"1 5\n" \
					"2 3\n" \
					"2 5\n" \
					"4 3\n" \
					"5 3\n" \
					"4 5");
	fclose(input);
	
	SolveColorizingGraf(INPUT_FILENAME, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	char ans[ANSWER_LINE_LEN] = {'\0'};
	fgets(ans, ANSWER_LINE_LEN, output);
	EXPECT_TRUE(strcmp(ans, "1 2 1 2 3") == 0);
}
