#include "core/aircraft.hpp"

#include <gtest/gtest.h>

TEST(Aircraft, SquawkCode_Initialization)
{
    SquawkCode sc;

    EXPECT_STREQ("0000", sc.GetString().c_str());
    EXPECT_TRUE(sc.IsValid());
}

TEST(Aircraft, SquawkCode_Operations)
{
    SquawkCode sc;
    // initial value of 0000
    EXPECT_EQ(sc.GetAsInt(), 0);
    EXPECT_EQ(sc.GetString(), "0000");

    // Test invalid input for Set() function
    EXPECT_THROW(
        {
            try
            {
                sc.Set(9, 9, 9, 9);
            }
            catch (const std::exception& e)
            {
                // and this tests that it has the correct message
                EXPECT_STREQ("Invalid squawk code digits (must be in range 0-7)", e.what());
                throw;
            }
        },
        std::invalid_argument);

    EXPECT_THROW(
        {
            try
            {
                sc.Set("9999");
            }
            catch (const std::exception& e)
            {
                // and this tests that it has the correct message
                EXPECT_STREQ(
                    "Invalid squawk code digits (there must be 4 digits & must be in range 0-7)",
                    e.what());
                throw;
            }
        },
        std::invalid_argument);

    // Set with valid input
    sc.Set("7777");
    EXPECT_EQ(sc.GetString(), "7777");
    EXPECT_EQ(sc.GetAsInt(), 7777);
}

TEST(Aircraft, AircraftState_Initialization)
{
    Aircraft a;
    EXPECT_EQ(0, a.GetFlightLevel());
    EXPECT_STREQ("0000", a.GetSquawkCode().c_str());
}