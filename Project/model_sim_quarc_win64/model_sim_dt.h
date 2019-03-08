/*
 * model_sim_dt.h
 *
 * Code generation for model "model_sim.mdl".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.1 (R2011b) 08-Jul-2011
 * C source code generated on : Fri Nov 23 11:24:13 2018
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
  { (char_T *)(&model_sim_B.AngleGain), 0, 0, 7 }
  ,

  { (char_T *)(&model_sim_DWork.HILInitialize_AIMinimums[0]), 0, 0, 24 },

  { (char_T *)(&model_sim_DWork.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&model_sim_DWork.HILReadEncoderTimebase_Task), 15, 0, 1 },

  { (char_T *)(&model_sim_DWork.Derivative_RWORK.TimeStampA), 0, 0, 2 },

  { (char_T *)(&model_sim_DWork.Angle_PWORK.LoggedData), 11, 0, 5 },

  { (char_T *)(&model_sim_DWork.HILInitialize_QuadratureModes[0]), 6, 0, 10 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&model_sim_P.positionGain1_Gain[0]), 0, 0, 26 },

  { (char_T *)(&model_sim_P.HILInitialize_CKChannels[0]), 6, 0, 8 },

  { (char_T *)(&model_sim_P.HILInitialize_AIChannels[0]), 7, 0, 17 },

  { (char_T *)(&model_sim_P.HILInitialize_Active), 8, 0, 37 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  4U,
  rtPTransitions
};

/* [EOF] model_sim_dt.h */
