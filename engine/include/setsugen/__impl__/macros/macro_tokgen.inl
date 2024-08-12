#pragma once

#define GENERATE_TOKEN(count, prefix, postfix) prefix##count##postfix

#pragma region __DoNotExpandThis__

#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_1(prefix, postfix)   GENERATE_TOKEN(1, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_2(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_1(prefix, postfix), GENERATE_TOKEN(2, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_3(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_2(prefix, postfix), GENERATE_TOKEN(3, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_4(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_3(prefix, postfix), GENERATE_TOKEN(4, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_5(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_4(prefix, postfix), GENERATE_TOKEN(5, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_6(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_5(prefix, postfix), GENERATE_TOKEN(6, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_7(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_6(prefix, postfix), GENERATE_TOKEN(7, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_8(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_7(prefix, postfix), GENERATE_TOKEN(8, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_9(prefix, postfix)   MACRO_GENERATE_SEQUENCE_OF_TOKEN_8(prefix, postfix), GENERATE_TOKEN(9, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_10(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_9(prefix, postfix), GENERATE_TOKEN(10, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_11(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_10(prefix, postfix), GENERATE_TOKEN(11, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_12(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_11(prefix, postfix), GENERATE_TOKEN(12, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_13(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_12(prefix, postfix), GENERATE_TOKEN(13, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_14(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_13(prefix, postfix), GENERATE_TOKEN(14, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_15(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_14(prefix, postfix), GENERATE_TOKEN(15, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_16(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_15(prefix, postfix), GENERATE_TOKEN(16, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_17(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_16(prefix, postfix), GENERATE_TOKEN(17, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_18(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_17(prefix, postfix), GENERATE_TOKEN(18, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_19(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_18(prefix, postfix), GENERATE_TOKEN(19, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_20(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_19(prefix, postfix), GENERATE_TOKEN(20, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_21(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_20(prefix, postfix), GENERATE_TOKEN(21, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_22(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_21(prefix, postfix), GENERATE_TOKEN(22, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_23(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_22(prefix, postfix), GENERATE_TOKEN(23, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_24(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_23(prefix, postfix), GENERATE_TOKEN(24, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_25(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_24(prefix, postfix), GENERATE_TOKEN(25, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_26(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_25(prefix, postfix), GENERATE_TOKEN(26, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_27(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_26(prefix, postfix), GENERATE_TOKEN(27, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_28(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_27(prefix, postfix), GENERATE_TOKEN(28, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_29(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_28(prefix, postfix), GENERATE_TOKEN(29, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_30(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_29(prefix, postfix), GENERATE_TOKEN(30, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_31(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_30(prefix, postfix), GENERATE_TOKEN(31, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_32(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_31(prefix, postfix), GENERATE_TOKEN(32, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_33(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_32(prefix, postfix), GENERATE_TOKEN(33, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_34(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_33(prefix, postfix), GENERATE_TOKEN(34, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_35(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_34(prefix, postfix), GENERATE_TOKEN(35, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_36(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_35(prefix, postfix), GENERATE_TOKEN(36, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_37(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_36(prefix, postfix), GENERATE_TOKEN(37, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_38(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_37(prefix, postfix), GENERATE_TOKEN(38, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_39(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_38(prefix, postfix), GENERATE_TOKEN(39, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_40(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_39(prefix, postfix), GENERATE_TOKEN(40, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_41(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_40(prefix, postfix), GENERATE_TOKEN(41, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_42(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_41(prefix, postfix), GENERATE_TOKEN(42, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_43(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_42(prefix, postfix), GENERATE_TOKEN(43, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_44(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_43(prefix, postfix), GENERATE_TOKEN(44, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_45(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_44(prefix, postfix), GENERATE_TOKEN(45, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_46(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_45(prefix, postfix), GENERATE_TOKEN(46, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_47(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_46(prefix, postfix), GENERATE_TOKEN(47, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_48(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_47(prefix, postfix), GENERATE_TOKEN(48, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_49(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_48(prefix, postfix), GENERATE_TOKEN(49, prefix, postfix)
#define MACRO_GENERATE_SEQUENCE_OF_TOKEN_50(prefix, postfix)  MACRO_GENERATE_SEQUENCE_OF_TOKEN_49(prefix, postfix), GENERATE_TOKEN(50, prefix, postfix)

#pragma endregion

#define MACRO_GENERATE_SEQUENCE_OF_TOKEN(count, prefix, postfix) \
    MACRO_EXPAND(MACRO_GENERATE_SEQUENCE_OF_TOKEN_##count(prefix, postfix))