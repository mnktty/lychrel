# -*- mode:org -*-

# A better way to define tests with a pipe separated text file, can be given extension .robot

| *** Settings ***|

| *Setting* | *Value*         |
| Library   | CheckLychrel.py |


| *Test Case*             | *Action*                | *Arguments* |          *Arguments* | *Arguments* |
| Valid Lychrel Numbers   |                         |             |                      |             |
|                         | Check Lychrel Number    |           1 |                    1 |           0 |
|                         | Check Lychrel Number    |           1 |                    1 |           0 |
|                         | Check Lychrel Number    |           2 |                    2 |           0 |
|                         | Check Lychrel Number    |          11 |                   11 |           0 |
|                         | Check Lychrel Number    |          21 |                   33 |           1 |
|                         | Check Lychrel Number    |          32 |                   55 |           1 |
|                         | Check Lychrel Number    |          89 |        8813200023188 |          24 |
|                         | Check Lychrel Number    |         121 |                  121 |           0 |
|                         | Check Lychrel Number    |         156 |                 6666 |           3 |
|                         | Check Lychrel Number    |         195 |                 9339 |           4 |
|                         | Check Lychrel Number    |         197 |               881188 |           7 |
|                         | Check Lychrel Number    |         246 |                  888 |           1 |
| Invalid Lychrel Numbers |                         |             |                      |             |
|                         | Check NonLychrel Number |         196 | 13305261530450734933 |          40 |

| *Keyword*            | *Action*       | *Arguments* | *Arguments*        | *Arguments*            |
| Check Lychrel Number | [arguments]    | ${num}      | ${expected_output} | ${expected_iterations} |
|                      | Verify Lychrel | ${num}      | ${expected_output} | ${expected_iterations} |

| Check NonLychrel Number | [arguments]                  | ${num}                             | ${expected_output} | ${expected_iterations} |                    |                        |
|                         | Run Keyword And Expect Error | No convergence after 40 iterations | Verify Lychrel     | ${num}                 | ${expected_output} | ${expected_iterations} |

