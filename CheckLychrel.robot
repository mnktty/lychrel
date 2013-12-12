| *** Settings *** | 

| Documentation | Checks (testcases) for validating lychrel numbers |
| Library       | CheckLychrel.py                                   |

| *** Test Case *** |

| Valid Lychrel Numbers |                      |                                              |               |    |
|                       | [Documentation]      | Check against a set of valid lychrel numbers |               |    |
|                       | [Tags]               |                                    essential |        sanity |    |
|                       | Check Lychrel Number |                                            1 |             1 |  0 |
|                       | Check Lychrel Number |                                            1 |             1 |  0 |
|                       | Check Lychrel Number |                                            2 |             2 |  0 |
|                       | Check Lychrel Number |                                           11 |            11 |  0 |
|                       | Check Lychrel Number |                                           21 |            33 |  1 |
|                       | Check Lychrel Number |                                           32 |            55 |  1 |
|                       | Check Lychrel Number |                                           89 | 8813200023188 | 24 |
|                       | Check Lychrel Number |                                          121 |           121 |  0 |
|                       | Check Lychrel Number |                                          156 |          6666 |  3 |
|                       | Check Lychrel Number |                                          195 |          9339 |  4 |
|                       | Check Lychrel Number |                                          197 |        881188 |  7 |
|                       | Check Lychrel Number |                                          246 |           888 |  1 |


| Invalid Lychrel Numbers |                         |     |                      |    |
|                         | Check NonLychrel Number | 196 | 13305261530450734933 | 40 |


| Run Unit Tests Written in C |                  |                                                  |
|                             | [Documentation]  | Trigger native executable for running unit tests |
|                             | Run C Unit Tests |                                                  |


| *** Keyword *** |

| Check Lychrel Number |                |        |                    |                        |
|                      | [Arguments]    | ${num} | ${expected_output} | ${expected_iterations} |
|                      | Verify Lychrel | ${num} | ${expected_output} | ${expected_iterations} |


| Check NonLychrel Number |                              |                                    |                    |                        |                    |                        |
|                         | [Arguments]                  | ${num}                             | ${expected_output} | ${expected_iterations} |                    |                        |
|                         | Run Keyword And Expect Error | No convergence after 40 iterations | Verify Lychrel     | ${num}                 | ${expected_output} | ${expected_iterations} |


| Run C Unit Tests |                                |
|                  | Run Unit Tests From Executable |
