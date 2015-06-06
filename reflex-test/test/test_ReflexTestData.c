#include "unity.h"
#include "ReflexTestData.h"

void setup(void) {
}

void tearDown(void) {
}

void testReflexTestData_InitShouldInitAllStateVariables() {
  // Set the internal state variables to various things
  ReflexTestData_SetResponseTime(1.234);
  ReflexTestData_IncrementIndex();
  ReflexTestData_GenerateSequence(123);
  ReflexTestData_SetPressedButton(0x4);
  ReflexTestData_SetCurrentState(show_info_st);
  ReflexTestData_SetMaxResponseTime(0.345);
  ReflexTestData_SetMinResponseTime(0.002);
  ReflexTestData_SetAverageResponseTime(0.123);

  // Call Init
  ReflexTestData_Init();

  // Verify that data was re-initialized
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetCurrentIndex());
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetResponseTime());
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetPressedButton());
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetMaxResponseTime());
  TEST_ASSERT_EQUAL(5, ReflexTestData_GetMinResponseTime());
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetAverageResponseTime());
  TEST_ASSERT_EQUAL(init_st, ReflexTestData_GetCurrentState());

  // NOTE: Sequence cannot be directly tested, but if the above worked,
  // the sequence will have been cleared as well.
}

void testReflexTestData_CheckIfIsCorrectButtonWorks() {
  ReflexTestData_Init();
  // Generate a sequence of:
  // {2, 2, 2, 3, 4, 4, 4, 3, 3, 2};
  ReflexTestData_GenerateSequence(123);

  // Set the button to the correct button
  ReflexTestData_SetPressedButton(2);
  TEST_ASSERT_TRUE(ReflexTestData_IsCorrectButtonPressed());

  // Set button to incorrect button
  ReflexTestData_SetPressedButton(1);
  TEST_ASSERT_FALSE(ReflexTestData_IsCorrectButtonPressed());
}

void testReflexTestData_IncrementIndexShouldOnlyIncrementToTotalLength() {
  ReflexTestData_Init();
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetCurrentIndex());

  int i;
  // Iterate more times than there are sequences
  for (i = 0; i < (REFLEXTESTDATA_SEQUENCE_LENGTH*2); i++) {
    ReflexTestData_IncrementIndex();
  }

  TEST_ASSERT_EQUAL(REFLEXTESTDATA_SEQUENCE_LENGTH, ReflexTestData_GetCurrentIndex());
}

void testReflexTestData_GetLEDShouldReturnCurrentLEDOfSequence() {
  ReflexTestData_Init();
  // Generate a sequence of:
  // {2, 4, 2, 3, 2, 3, 4, 2, 4, 4};
  ReflexTestData_GenerateSequence(88);

  TEST_ASSERT_EQUAL(2, ReflexTestData_GetLed());
}

void testReflexTestData_IsSequenceDoneShouldReturnTrueWhenIndexReachesEnd() {
  ReflexTestData_Init();

  TEST_ASSERT_FALSE(ReflexTestData_IsSequenceDone());

  // Increment the index to the end.
  int i;
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH; i++) {
    ReflexTestData_IncrementIndex();
  }

  TEST_ASSERT_TRUE(ReflexTestData_IsSequenceDone());
}

void testReflexTestData_UpdateScoresShouldSortTheListOfHighScores() {
  // In order to automatically test this, we will need to:
  //  1. Get the pointer to the high scores array
  //  2. Set it to known values
  //  3. Call update_scores_st
  //  4. Verify that the sorting is correct.
  TEST_IGNORE_MESSAGE("Still need to implement this test.");
}
