#pragma once
#include <Arduino.h>

struct UsageData {
    float session_pct;       // utilization 0-100 (5h window Pro/Max; spending % Enterprise)
    int session_reset_mins;  // minutes until reset
    float weekly_pct;        // 7-day utilization (Pro/Max only; 0 for Enterprise)
    int weekly_reset_mins;   // minutes until weekly reset (Pro/Max only)
    char status[16];         // "allowed", "limited", etc.
    bool chime;              // play the session-reset chime; false unless daemon opts in
    bool enterprise;         // true = Enterprise spending-limit account
    int time_pct;            // 0-100: fraction of billing period elapsed (Enterprise)
    int period_days;         // total billing period length in days (Enterprise)
    char reset_date[12];     // formatted reset date e.g. "Jul 1" (Enterprise)

    // Budget/spend-pace fields (Enterprise only, and only when the daemon has
    // a configured `budget_usd` — see README). budget_usd == 0 means none of
    // these are populated; the UI falls back to the plain pace-label view.
    int budget_usd;          // configured monthly budget, USD; 0 = not configured
    int projected_usd;       // projected total spend by period end at current pace, USD
    int avg_per_day_usd;     // budget_usd / period_days, USD — the flat daily reference
    static const int MAX_DAILY = 7;  // a week, ending today — see daemon's add_budget_fields
    int daily_usd[MAX_DAILY];  // USD spent each day, oldest first, today last
    int daily_count;           // how many of daily_usd are populated (< 7 in the period's first week)
    long clock_epoch;        // local wall-clock epoch (s) from daemon; 0 = not provided
    int  clock_fmt;          // 12 or 24 (hour format from daemon); defaults to 24
    bool ok;                 // data parse succeeded
    bool valid;              // false until first successful parse
};
