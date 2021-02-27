#ifndef YAYA_LOGGER_H_
#define YAYA_LOGGER_H_

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "yaya_logger_struct.h"
#include "yaya_logger_macro.h"
#include "yaya_logger_conf.h"

// clang-format off

#if LOGGER_LOGS == LOGGER_TRUE

#define loggerf(...) \
        ___LOGGER_FUNC_x( ,            \
        ##__VA_ARGS__ ,                \
        ___LOGGER_FUNC_Z(__VA_ARGS__), \
        ___LOGGER_FUNC_Y(__VA_ARGS__), \
        ___LOGGER_FUNC_X(__VA_ARGS__), \
        ___LOGGER_FUNC_W(__VA_ARGS__), \
        ___LOGGER_FUNC_V(__VA_ARGS__), \
        ___LOGGER_FUNC_U(__VA_ARGS__), \
        ___LOGGER_FUNC_T(__VA_ARGS__), \
        ___LOGGER_FUNC_S(__VA_ARGS__), \
        ___LOGGER_FUNC_R(__VA_ARGS__), \
        ___LOGGER_FUNC_Q(__VA_ARGS__), \
        ___LOGGER_FUNC_P(__VA_ARGS__), \
        ___LOGGER_FUNC_O(__VA_ARGS__), \
        ___LOGGER_FUNC_N(__VA_ARGS__), \
        ___LOGGER_FUNC_M(__VA_ARGS__), \
        ___LOGGER_FUNC_L(__VA_ARGS__), \
        ___LOGGER_FUNC_K(__VA_ARGS__), \
        ___LOGGER_FUNC_J(__VA_ARGS__), \
        ___LOGGER_FUNC_I(__VA_ARGS__), \
        ___LOGGER_FUNC_H(__VA_ARGS__), \
        ___LOGGER_FUNC_G(__VA_ARGS__), \
        ___LOGGER_FUNC_F(__VA_ARGS__), \
        ___LOGGER_FUNC_E(__VA_ARGS__), \
        ___LOGGER_FUNC_D(__VA_ARGS__), \
        ___LOGGER_FUNC_C(__VA_ARGS__), \
        ___LOGGER_FUNC_B(__VA_ARGS__), \
        ___LOGGER_FUNC_A(__VA_ARGS__), \
        ___LOGGER_FUNC_0(__VA_ARGS__))

#define ___LOGGER_FUNC_x(x, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, FUNC, ...) FUNC

#define ___LOGGER_FUNC_0()                ___logger_func_0()
#define ___LOGGER_FUNC_A(A)               ___logger_func_1(A)
#define ___LOGGER_FUNC_B(A, ...)          ___logger_func_2(A, __VA_ARGS__)
#define ___LOGGER_FUNC_C(A, B, ...)       ___logger_func_3(A, B, __VA_ARGS__)
#define ___LOGGER_FUNC_D(A, B, C, ...)    ___logger_func_4(A, B, C, __VA_ARGS__)
#define ___LOGGER_FUNC_E(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_F(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_G(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_H(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_I(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_J(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_K(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_L(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_M(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_O(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_P(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_Q(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_R(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_S(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_T(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_U(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_V(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_W(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_X(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_Y(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)
#define ___LOGGER_FUNC_Z(A, B, C, D, ...) ___logger_func_5(A, B, C, D, __VA_ARGS__)


/*
A - struct [logger*]
B - int    [l1]
C - int    [l2]
D - str    [char*] >-.
E - va     [...]   <-'

A      ->  logger*
A      ->  l1
A      ->  l2
A      ->  char*

AB     ->  logger*, l1
AC     ->  logger*, l2
AD     ->  logger*, char*
BC     ->  l1     , l2
BD     ->  l1     , char*
CD     ->  l1     , char*
DE     ->  char*  , va

ABC    ->  logger*, l1  , l1
ABD    ->  logger*, l1  , char*
ACD    ->  logger*, iL2  , char*
ADE    ->  logger*, char*, va
BCD    ->  l1    , l2  , char*
BDE    ->  l1    , char*, va
CDE    ->  l2    , char*, va
DEE    ->  DE

ABCD   ->  logger*, l1  , l1  , char*
ABDE   ->  logger*, l1  , char*, va
ACDE   ->  logger*, l2  , char*, va
ADEE   ->  ADE
BCDE   ->  l1    , l1  , char*, va
BDEE   ->  BDE
CDEE   ->  CDE
DEEE   ->  DE

ABCDE  ->  logger*, l1  , l1  , char*, va
ABDEE  ->  ABDE
ACDEE  ->  ACDE
ADEEE  ->  ADE
BCDEE  ->  BCDE
BDEEE  ->  BDE
CDEEE  ->  CDE
DEEEE  ->  DE
*/


#define ___logger_func_0( ) \
                  ___logger_func_______("log_0______")


#define ___logger_func_1(a) \
    _Generic((a),                                          \
    ___logger*  : ___logger_func_A_____("log_1_A____", a), \
    ___l1_type  : ___logger_func__B____("log_1__B___", a), \
    ___l2_type  : ___logger_func___C___("log_1___C__", a), \
    char*       : ___logger_func____D__("log_1____D_", a), \
    default     : ___logger_func______V("log_1___V_1"))


#define ___logger_func_2(a, ...) \
    _Generic((a),                                                                                \
    ___logger*  : _Generic((__VA_ARGS__),                                                        \
                  ___l1_type            : ___logger_func_AB____("log_2_AB___", a, __VA_ARGS__),  \
                  ___l2_type            : ___logger_func_A_C___("log_2_A_C__", a, __VA_ARGS__),  \
                  char*                 : ___logger_func_A__D__("log_2_A__D_", a, __VA_ARGS__),  \
                  default               : ___logger_func______V("log_2___V_1")),                 \
    ___l1_type  : _Generic((__VA_ARGS__),                                                        \
                  ___l2_type            : ___logger_func__BC___("log_2__BC__", a, __VA_ARGS__),  \
                  char*                 : ___logger_func__B_D__("log_2__B_D_", a, __VA_ARGS__),  \
                  default               : ___logger_func______V("log_2___V_2")),                 \
    ___l2_type     : _Generic((__VA_ARGS__),                                                     \
                  char*                 : ___logger_func___CD__("log_2___CD_", a, __VA_ARGS__),  \
                  default               : ___logger_func______V("log_2___V_3")),                 \
    char*       : _Generic((__VA_ARGS__),                                                        \
                  default               : ___logger_func____DE_("log_2____DE", a, __VA_ARGS__)), \
    default                             : ___logger_func______V("log_2___V_4"))


#define ___logger_func_3(a, b, ...) \
    _Generic((a),                                                                                                  \
    ___logger*  : _Generic((b),                                                                                    \
                  ___l1_type  : _Generic((__VA_ARGS__),                                                            \
                                ___l2_type            : ___logger_func_ABC___("log_3_ABC__", a, b, __VA_ARGS__),   \
                                char*                 : ___logger_func_AB_D__("log_3_AB_D_", a, b, __VA_ARGS__),   \
                                default               : ___logger_func______V("log_3___V_1")),                     \
                  ___l2_type  : _Generic((__VA_ARGS__),                                                            \
                                char*                 : ___logger_func_A_CD__("log_3_A_CD_", a, b, __VA_ARGS__),   \
                                default               : ___logger_func______V("log_3___V_2")),                     \
                  char*       : _Generic((__VA_ARGS__),                                                            \
                                default               : ___logger_func_A__DE_("log_3_A__DE", a, b, __VA_ARGS__)),  \
                  default                             : ___logger_func______V("log_3___V_3")),                     \
    ___l1_type  : _Generic((b),                                                                                    \
                  ___l2_type  : _Generic((__VA_ARGS__),                                                            \
                                char*                 : ___logger_func__BCD__("log_3__BCD_", a, b, __VA_ARGS__),   \
                                default               : ___logger_func______V("log_3___V_4")),                     \
                  char*       : _Generic((__VA_ARGS__),                                                            \
                                default               : ___logger_func__B_DE_("log_3__B_DE", a, b, __VA_ARGS__)),  \
                  default                             : ___logger_func______V("log_3___V_5")),                     \
    ___l2_type  : _Generic((b),                                                                                    \
                  char*       : _Generic((__VA_ARGS__),                                                            \
                                default               : ___logger_func___CDE_("log_3___CDE", a, b, __VA_ARGS__)),  \
                  default                             : ___logger_func______V("log_3___V_6")),                     \
    char*       : _Generic((b),                                                                                    \
                  default     : _Generic((__VA_ARGS__),                                                            \
                                default               : ___logger_func____DE_("log_3____DE", a, b, __VA_ARGS__))), \
    default                                           : ___logger_func______V("log_3___V_7"))


#define ___logger_func_4(a, b, c, ...) \
    _Generic((a),                                                                                                                    \
    ___logger*  : _Generic((b),                                                                                                      \
                  ___l1_type  : _Generic((c),                                                                                        \
                                ___l2_type  : _Generic((__VA_ARGS__),                                                                \
                                              char*                 : ___logger_func_ABCD__("log_4_ABCD_", a, b, c, __VA_ARGS__),    \
                                              default               : ___logger_func______V("log_4___V_1")),                         \
                                char*       : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func_AB_DE_("log_4_AB_DE", a, b, c, __VA_ARGS__)),   \
                                default                             : ___logger_func______V("log_4___V_2")),                         \
                  ___l2_type  : _Generic((c),                                                                                        \
                                char*       : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func_A_CDE_("log_4_A_CDE", a, b, c, __VA_ARGS__)),   \
                                default                             : ___logger_func______V("log_4___V_3")),                         \
                  char*       : _Generic((c),                                                                                        \
                                default     : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func_A__DE_("log_4_A__DE", a, b, c, __VA_ARGS__))),  \
                  default                                           : ___logger_func______V("log_4___V_4")),                         \
    ___l1_type  : _Generic((b),                                                                                                      \
                  ___l2_type  : _Generic((c),                                                                                        \
                                char*       : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func__BCDE_("log_4__BCDE", a, b, c, __VA_ARGS__)),   \
                                default                             : ___logger_func______V("log_4___V_5")),                         \
                  char*       : _Generic((c),                                                                                        \
                                default     : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func__B_DE_("log_4__B_DE", a, b, c, __VA_ARGS__))),  \
                  default                                           : ___logger_func______V("log_4___V_6")),                         \
    ___l2_type  : _Generic((b),                                                                                                      \
                  char*       : _Generic((c),                                                                                        \
                                default     : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func___CDE_("log_4___CDE", a, b, c, __VA_ARGS__))),  \
                  default                                           : ___logger_func______V("log_4___V_7")),                         \
    char*       : _Generic((b),                                                                                                      \
                  default     : _Generic((c),                                                                                        \
                                default     : _Generic((__VA_ARGS__),                                                                \
                                              default               : ___logger_func____DE_("log_4____DE", a, b, c, __VA_ARGS__)))), \
    default                                                         : ___logger_func______V("log_4___V_8"))


#define ___logger_func_5(a, b, c, d, ...) \
    _Generic((a),                                                                                                                                       \
    ___logger*  : _Generic((b),                                                                                                                         \
                  ___l1_type  : _Generic((c),                                                                                                           \
                                ___l2_type  : _Generic((d),                                                                                             \
                                              char*       :  _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func_ABCDE_("log_5_ABCDE", a, b, c, d, __VA_ARGS__)),    \
                                              default                              : ___logger_func______V("log_5___V_1")),                             \
                                char*       : _Generic((d),                                                                                             \
                                              default     :  _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func_AB_DE_("log_5_AB_DE", a, b, c, d, __VA_ARGS__))),   \
                                default                                            : ___logger_func______V("log_5___V_2")),                             \
                  ___l2_type  : _Generic((c),                                                                                                           \
                                char*       : _Generic((d),                                                                                             \
                                              default     :  _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func_A_CDE_("log_5_A_CDE", a, b, c, d, __VA_ARGS__))),   \
                                default                                            : ___logger_func______V("log_5___V_3")),                             \
                  char*       : _Generic((c),                                                                                                           \
                                default      : _Generic((d),                                                                                            \
                                               default     : _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func_A__DE_("log_5_A__DE", a, b, c, d, __VA_ARGS__)))),  \
                  default                                                          : ___logger_func______V("log_5___V_4")),                             \
    ___l1_type  : _Generic((b),                                                                                                                         \
                  ___l2_type  : _Generic((c),                                                                                                           \
                                char*       :  _Generic((d),                                                                                            \
                                               default     : _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func__BCDE_("log_5__BCDE", a, b, c, d, __VA_ARGS__))),   \
                                default                                            : ___logger_func______V("log_5___V_5")),                             \
                  char*       : _Generic((c),                                                                                                           \
                                default     :  _Generic((d),                                                                                            \
                                               default     : _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func__B_DE_("log_5__B_DE", a, b, c, d, __VA_ARGS__)))),  \
                  default                                                          : ___logger_func______V("log_5___V_6")),                             \
    ___l2_type  : _Generic((b),                                                                                                                         \
                  char*       : _Generic((c),                                                                                                           \
                                default     :  _Generic((d),                                                                                            \
                                               default     : _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func___CDE_("log_5___CDE", a, b, c, d, __VA_ARGS__)))),  \
                  default                                                          : ___logger_func______V("log_5___V_7")),                             \
    char*       : _Generic((b),                                                                                                                         \
                  default     : _Generic((c),                                                                                                           \
                                default     :  _Generic((d),                                                                                            \
                                               default     : _Generic((__VA_ARGS__),                                                                    \
                                                             default               : ___logger_func____DE_("log_5____DE", a, b, c, d, __VA_ARGS__))))), \
    default                                                                        : ___logger_func______V("log_5___V_8"))



#if LOGGER_DEF == LOGGER_TRUE
#define ___LOGGER_LVG ___logger_main_def
#endif


#define ___LOGGER_LP_OR_DEF(A) _Generic((A), ___logger* : (A), default : (___LOGGER_LVG) )
#define ___LOGGER_L1_OR_DEF(A) _Generic((A), ___l1_type : (A), default : (L_VOID)     )
#define ___LOGGER_L2_OR_DEF(A) _Generic((A), ___l2_type : (A), default : (LL_VOID)    )
#define ___LOGGER_CP_OR_DEF(A) _Generic((A), char*      : (A), default : (NULL)       )

#define ___logger_func______V(N)                  yaya_log_defl(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG)

#define ___logger_func_______(N)                  yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , L_VOID                , LL_VOID               , NULL                  , NULL       )

#define ___logger_func_A_____(N, A)               yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), L_VOID                , LL_VOID               , NULL                  , NULL       )
#define ___logger_func__B____(N, B)               yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , ___LOGGER_L1_OR_DEF(B), LL_VOID               , NULL                  , NULL       )
#define ___logger_func___C___(N, C)               yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , LL_VOID               , ___LOGGER_L2_OR_DEF(C), NULL                  , NULL       )
#define ___logger_func____D__(N, D)               yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , L_VOID                , LL_VOID               , ___LOGGER_CP_OR_DEF(D), NULL       )

#define ___logger_func_AB____(N, A, B)            yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), ___LOGGER_L1_OR_DEF(B), LL_VOID               , NULL                  , NULL       )
#define ___logger_func_A_C___(N, A, C)            yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), L_VOID                , ___LOGGER_L2_OR_DEF(C), NULL                  , NULL       )
#define ___logger_func_A__D__(N, A, D)            yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), L_VOID                , LL_VOID               , ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func__BC___(N, B, C)            yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , ___LOGGER_L1_OR_DEF(B), ___LOGGER_L2_OR_DEF(C), NULL                  , NULL       )
#define ___logger_func__B_D__(N, B, D)            yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , ___LOGGER_L1_OR_DEF(B), LL_VOID               , ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func___CD__(N, C, D)            yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , L_VOID                , ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func____DE_(N, D, ...)          yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , L_VOID                , LL_VOID               , ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)

#define ___logger_func_ABC___(N, A, B, C)         yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), ___LOGGER_L1_OR_DEF(B), ___LOGGER_L2_OR_DEF(C), NULL                  , NULL       )
#define ___logger_func_AB_D__(N, A, B, D)         yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), ___LOGGER_L1_OR_DEF(B), LL_VOID               , ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func_A_CD__(N, A, C, D)         yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), L_VOID                , ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func_A__DE_(N, A, D, ...)       yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), L_VOID                , LL_VOID               , ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)
#define ___logger_func__BCD__(N, B, C, D)         yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , ___LOGGER_L1_OR_DEF(B), ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func__B_DE_(N, B, D, ...)       yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , ___LOGGER_L1_OR_DEF(B), LL_VOID               , ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)
#define ___logger_func___CDE_(N, C, D, ...)       yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , L_VOID                , ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)

#define ___logger_func_ABCD__(N, A, B, C, D)      yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), ___LOGGER_L1_OR_DEF(B), ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), NULL       )
#define ___logger_func_AB_DE_(N, A, B, D, ...)    yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), ___LOGGER_L1_OR_DEF(B), LL_VOID               , ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)
#define ___logger_func_A_CDE_(N, A, C, D, ...)    yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), L_VOID                , ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)
#define ___logger_func__BCDE_(N, B, C, D, ...)    yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LVG         , ___LOGGER_L1_OR_DEF(B), ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)

#define ___logger_func_ABCDE_(N, A, B, C, D, ...) yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, N, ___LOGGER_LP_OR_DEF(A), ___LOGGER_L1_OR_DEF(B), ___LOGGER_L2_OR_DEF(C), ___LOGGER_CP_OR_DEF(D), __VA_ARGS__)



#define loggerf_init(...) \
        ___LOGGER_INIT_x( ,            \
        ##__VA_ARGS__ ,                \
        ___LOGGER_INIT_F(__VA_ARGS__), \
        ___LOGGER_INIT_E(__VA_ARGS__), \
        ___LOGGER_INIT_D(__VA_ARGS__), \
        ___LOGGER_INIT_C(__VA_ARGS__), \
        ___LOGGER_INIT_B(__VA_ARGS__), \
        ___LOGGER_INIT_A(__VA_ARGS__), \
        ___LOGGER_INIT_0(__VA_ARGS__))

#define ___LOGGER_INIT_x(x, A, B, C, D, E, F, FUNC, ...) FUNC

#define ___LOGGER_INIT_0()                 yaya_log_init(&___LOGGER_LVG, NULL, NULL, NULL, NULL, NULL)
#define ___LOGGER_INIT_A(A)                yaya_log_init(A             , NULL, NULL, NULL, NULL, NULL)
#define ___LOGGER_INIT_B(A, B)             yaya_log_init(A             , B   , NULL, NULL, NULL, NULL)
#define ___LOGGER_INIT_C(A, B, C)          yaya_log_init(A             , B   , C   , NULL, NULL, NULL)
#define ___LOGGER_INIT_D(A, B, C, D)       yaya_log_init(A             , B   , C   , D   , NULL, NULL)
#define ___LOGGER_INIT_E(A, B, C, D, E)    yaya_log_init(A             , B   , C   , D   , E   , NULL)
#define ___LOGGER_INIT_F(A, B, C, D, E, F) yaya_log_init(A             , B   , C   , D   , E   , F   )

#else

#define loggerf(...)      //логгер
#define loggerf_init(...) //инициализация

#endif

uintmax_t yaya_log_init(___logger** lvg, ___logger_filter *type, ___logger_filter *name, ___logger_setting *setting, ___logger_define *define, ___logger_style *style);
uintmax_t yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, const char* debug, ___logger *lvg, ___l1_type type_one, ___l2_type type_two, const char *mes, ...);
uintmax_t yaya_log_defl(uintmax_t count, char *file, uintmax_t line, const char *func, const char* debug, ___logger *lvg);

void loggerf_test_param();
void loggerf_test_format();

// clang-format on

#endif /*YAYA_LOGGER_H_*/
