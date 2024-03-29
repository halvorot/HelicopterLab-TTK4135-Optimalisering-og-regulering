/*
 * helicopter_10_3_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_10_3".
 *
 * Model version              : 1.186
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
<<<<<<< HEAD
 * C source code generated on : Wed Feb 20 14:22:05 2019
=======
 * C source code generated on : Wed Feb 06 14:52:16 2019
>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_card),
  sizeof(t_task)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_card",
  "t_task"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&helicopter_10_3_B.TravelCounttorad), 0, 0, 17 }
  ,

  { (char_T *)(&helicopter_10_3_DW.HILInitialize_AIMinimums[0]), 0, 0, 70 },

  { (char_T *)(&helicopter_10_3_DW.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&helicopter_10_3_DW.HILReadEncoderTimebase_Task), 15, 0, 1 },

  { (char_T *)(&helicopter_10_3_DW.ToFile_PWORK.FilePtr), 11, 0, 16 },

  { (char_T *)(&helicopter_10_3_DW.HILInitialize_ClockModes[0]), 6, 0, 46 },

  { (char_T *)(&helicopter_10_3_DW.HILInitialize_POSortedChans[0]), 7, 0, 8 },

  { (char_T *)(&helicopter_10_3_DW.ToFile_IWORK.Count), 10, 0, 4 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  8U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&helicopter_10_3_P.K[0]), 0, 0, 28 },

  { (char_T *)(&helicopter_10_3_P.HILReadEncoderTimebase_clock), 6, 0, 10 },

  { (char_T *)(&helicopter_10_3_P.HILInitialize_analog_input_chan[0]), 7, 0, 39
  },

  { (char_T *)(&helicopter_10_3_P.HILInitialize_active), 8, 0, 35 },

  { (char_T *)(&helicopter_10_3_P.TravelCounttorad_Gain), 0, 0, 32 },

  { (char_T *)(&helicopter_10_3_P.HILReadEncoderTimebase_Active), 8, 0, 2 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  6U,
  rtPTransitions
};

/* [EOF] helicopter_10_3_dt.h */
