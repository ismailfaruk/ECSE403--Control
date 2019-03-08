/*
 * test.c
 *
 * Code generation for model "test.mdl".
 *
 * Model version              : 1.1
 * Simulink Coder version : 8.1 (R2011b) 08-Jul-2011
 * C source code generated on : Fri Nov 09 13:44:58 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "test.h"
#include "test_private.h"
#include "test_dt.h"

/* Block signals (auto storage) */
BlockIO_test test_B;

/* Continuous states */
ContinuousStates_test test_X;

/* Block states (auto storage) */
D_Work_test test_DWork;

/* Real-time model */
RT_MODEL_test test_M_;
RT_MODEL_test *const test_M = &test_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  test_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void test_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  if (rtmIsMajorTimeStep(test_M)) {
    /* set solver stop time */
    if (!(test_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&test_M->solverInfo, ((test_M->Timing.clockTickH0 +
        1) * test_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&test_M->solverInfo, ((test_M->Timing.clockTick0 + 1)
        * test_M->Timing.stepSize0 + test_M->Timing.clockTickH0 *
        test_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(test_M)) {
    test_M->Timing.t[0] = rtsiGetT(&test_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(test_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: test/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(test_DWork.HILReadEncoderTimebase_Task, 1,
        &test_DWork.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          test_DWork.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          test_DWork.HILReadEncoderTimebase_Buffer[1];
      }
    }

    /* Gain: '<Root>/Angle Gain' */
    test_B.AngleGain = test_P.AngleGain_Gain * rtb_HILReadEncoderTimebase_o2;

    /* Abs: '<Root>/Abs' */
    test_B.Abs = fabs(test_B.AngleGain);

    /* Gain: '<Root>/position Gain' */
    test_B.positionGain = test_P.positionGain_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  test_B.TransferFcn = test_P.TransferFcn_C*test_X.TransferFcn_CSTATE;

  /* TransferFcn: '<Root>/Transfer Fcn1' */
  test_B.TransferFcn1 = test_P.TransferFcn1_C*test_X.TransferFcn1_CSTATE;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/position Gain1'
   *  SignalConversion: '<Root>/TmpSignal ConversionAtposition Gain1Inport1'
   *  Sum: '<Root>/Sum'
   */
  if (test_B.Abs >= test_P.Switch_Threshold) {
    test_B.Switch = test_P.Constant_Value;
  } else {
    test_B.Switch = test_P.Constant_Value - (((test_P.positionGain1_Gain[0] *
      test_B.positionGain + test_P.positionGain1_Gain[1] * test_B.TransferFcn) +
      test_P.positionGain1_Gain[2] * test_B.AngleGain) +
      test_P.positionGain1_Gain[3] * test_B.TransferFcn1);
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(test_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: test/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(test_DWork.HILInitialize_Card,
        &test_P.HILWriteAnalog_Channels, 1, &test_B.Switch);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
      }
    }
  }

  /* Derivative: '<Root>/Derivative' */
  {
    real_T t = test_M->Timing.t[0];
    real_T timeStampA = test_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = test_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &test_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      test_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &test_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &test_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      test_B.Derivative = (test_B.positionGain - *lastU++) / deltaT;
    }
  }

  /* Derivative: '<Root>/Derivative1' */
  {
    real_T t = test_M->Timing.t[0];
    real_T timeStampA = test_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = test_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &test_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      test_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &test_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &test_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      test_B.Derivative1 = (test_B.AngleGain - *lastU++) / deltaT;
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void test_update(int_T tid)
{
  /* Update for Derivative: '<Root>/Derivative' */
  {
    real_T timeStampA = test_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = test_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &test_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &test_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &test_DWork.Derivative_RWORK.TimeStampB;
        lastU = &test_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &test_DWork.Derivative_RWORK.TimeStampB;
        lastU = &test_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = test_M->Timing.t[0];
    *lastU++ = test_B.positionGain;
  }

  /* Update for Derivative: '<Root>/Derivative1' */
  {
    real_T timeStampA = test_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = test_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &test_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &test_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &test_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &test_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &test_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &test_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = test_M->Timing.t[0];
    *lastU++ = test_B.AngleGain;
  }

  if (rtmIsMajorTimeStep(test_M)) {
    rt_ertODEUpdateContinuousStates(&test_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++test_M->Timing.clockTick0)) {
    ++test_M->Timing.clockTickH0;
  }

  test_M->Timing.t[0] = rtsiGetSolverStopTime(&test_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++test_M->Timing.clockTick1)) {
      ++test_M->Timing.clockTickH1;
    }

    test_M->Timing.t[1] = test_M->Timing.clockTick1 * test_M->Timing.stepSize1 +
      test_M->Timing.clockTickH1 * test_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void test_derivatives(void)
{
  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  {
    ((StateDerivatives_test *) test_M->ModelData.derivs)->TransferFcn_CSTATE =
      test_B.Derivative;
    ((StateDerivatives_test *) test_M->ModelData.derivs)->TransferFcn_CSTATE +=
      (test_P.TransferFcn_A)*test_X.TransferFcn_CSTATE;
  }

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  {
    ((StateDerivatives_test *) test_M->ModelData.derivs)->TransferFcn1_CSTATE =
      test_B.Derivative1;
    ((StateDerivatives_test *) test_M->ModelData.derivs)->TransferFcn1_CSTATE +=
      (test_P.TransferFcn1_A)*test_X.TransferFcn1_CSTATE;
  }
}

/* Model initialize function */
void test_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)test_M, 0,
                sizeof(RT_MODEL_test));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&test_M->solverInfo, &test_M->Timing.simTimeStep);
    rtsiSetTPtr(&test_M->solverInfo, &rtmGetTPtr(test_M));
    rtsiSetStepSizePtr(&test_M->solverInfo, &test_M->Timing.stepSize0);
    rtsiSetdXPtr(&test_M->solverInfo, &test_M->ModelData.derivs);
    rtsiSetContStatesPtr(&test_M->solverInfo, &test_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&test_M->solverInfo, &test_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&test_M->solverInfo, (&rtmGetErrorStatus(test_M)));
    rtsiSetRTModelPtr(&test_M->solverInfo, test_M);
  }

  rtsiSetSimTimeStep(&test_M->solverInfo, MAJOR_TIME_STEP);
  test_M->ModelData.intgData.f[0] = test_M->ModelData.odeF[0];
  test_M->ModelData.contStates = ((real_T *) &test_X);
  rtsiSetSolverData(&test_M->solverInfo, (void *)&test_M->ModelData.intgData);
  rtsiSetSolverName(&test_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = test_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    test_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    test_M->Timing.sampleTimes = (&test_M->Timing.sampleTimesArray[0]);
    test_M->Timing.offsetTimes = (&test_M->Timing.offsetTimesArray[0]);

    /* task periods */
    test_M->Timing.sampleTimes[0] = (0.0);
    test_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    test_M->Timing.offsetTimes[0] = (0.0);
    test_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(test_M, &test_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = test_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    test_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(test_M, -1);
  test_M->Timing.stepSize0 = 0.002;
  test_M->Timing.stepSize1 = 0.002;

  /* external mode info */
  test_M->Sizes.checksums[0] = (3784546298U);
  test_M->Sizes.checksums[1] = (1416022897U);
  test_M->Sizes.checksums[2] = (4121089621U);
  test_M->Sizes.checksums[3] = (1410388266U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test_M->extModeInfo,
      &test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_M->extModeInfo, test_M->Sizes.checksums);
    rteiSetTPtr(test_M->extModeInfo, rtmGetTPtr(test_M));
  }

  test_M->solverInfoPtr = (&test_M->solverInfo);
  test_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&test_M->solverInfo, 0.002);
  rtsiSetSolverMode(&test_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  test_M->ModelData.blockIO = ((void *) &test_B);
  (void) memset(((void *) &test_B), 0,
                sizeof(BlockIO_test));

  /* parameters */
  test_M->ModelData.defaultParam = ((real_T *)&test_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &test_X;
    test_M->ModelData.contStates = (x);
    (void) memset((void *)&test_X, 0,
                  sizeof(ContinuousStates_test));
  }

  /* states (dwork) */
  test_M->Work.dwork = ((void *) &test_DWork);
  (void) memset((void *)&test_DWork, 0,
                sizeof(D_Work_test));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    test_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }
}

/* Model terminate function */
void test_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: test/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(test_DWork.HILInitialize_Card);
    hil_monitor_stop_all(test_DWork.HILInitialize_Card);
    is_switching = false;
    if ((test_P.HILInitialize_AOTerminate && !is_switching) ||
        (test_P.HILInitialize_AOExit && is_switching)) {
      test_DWork.HILInitialize_AOVoltages[0] = test_P.HILInitialize_AOFinal;
      test_DWork.HILInitialize_AOVoltages[1] = test_P.HILInitialize_AOFinal;
      test_DWork.HILInitialize_AOVoltages[2] = test_P.HILInitialize_AOFinal;
      test_DWork.HILInitialize_AOVoltages[3] = test_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &test_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
      }
    }

    hil_task_delete_all(test_DWork.HILInitialize_Card);
    hil_monitor_delete_all(test_DWork.HILInitialize_Card);
    hil_close(test_DWork.HILInitialize_Card);
    test_DWork.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  test_output(tid);
}

void MdlUpdate(int_T tid)
{
  test_update(tid);
}

void MdlInitializeSizes(void)
{
  test_M->Sizes.numContStates = (2);   /* Number of continuous states */
  test_M->Sizes.numY = (0);            /* Number of model outputs */
  test_M->Sizes.numU = (0);            /* Number of model inputs */
  test_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  test_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  test_M->Sizes.numBlocks = (20);      /* Number of blocks */
  test_M->Sizes.numBlockIO = (8);      /* Number of block outputs */
  test_M->Sizes.numBlockPrms = (89);   /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  test_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  test_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  test_DWork.Derivative_RWORK.TimeStampA = rtInf;
  test_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  test_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  test_DWork.Derivative1_RWORK.TimeStampB = rtInf;
}

void MdlStart(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: test/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &test_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(test_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((test_P.HILInitialize_CKPStart && !is_switching) ||
        (test_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(test_DWork.HILInitialize_Card, (t_clock *)
        test_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        test_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(test_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(test_M, _rt_error_message);
      return;
    }

    if ((test_P.HILInitialize_AIPStart && !is_switching) ||
        (test_P.HILInitialize_AIPEnter && is_switching)) {
      test_DWork.HILInitialize_AIMinimums[0] = test_P.HILInitialize_AILow;
      test_DWork.HILInitialize_AIMinimums[1] = test_P.HILInitialize_AILow;
      test_DWork.HILInitialize_AIMinimums[2] = test_P.HILInitialize_AILow;
      test_DWork.HILInitialize_AIMinimums[3] = test_P.HILInitialize_AILow;
      test_DWork.HILInitialize_AIMaximums[0] = test_P.HILInitialize_AIHigh;
      test_DWork.HILInitialize_AIMaximums[1] = test_P.HILInitialize_AIHigh;
      test_DWork.HILInitialize_AIMaximums[2] = test_P.HILInitialize_AIHigh;
      test_DWork.HILInitialize_AIMaximums[3] = test_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_AIChannels, 4U,
        &test_DWork.HILInitialize_AIMinimums[0],
        &test_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }

    if ((test_P.HILInitialize_AOPStart && !is_switching) ||
        (test_P.HILInitialize_AOPEnter && is_switching)) {
      test_DWork.HILInitialize_AOMinimums[0] = test_P.HILInitialize_AOLow;
      test_DWork.HILInitialize_AOMinimums[1] = test_P.HILInitialize_AOLow;
      test_DWork.HILInitialize_AOMinimums[2] = test_P.HILInitialize_AOLow;
      test_DWork.HILInitialize_AOMinimums[3] = test_P.HILInitialize_AOLow;
      test_DWork.HILInitialize_AOMaximums[0] = test_P.HILInitialize_AOHigh;
      test_DWork.HILInitialize_AOMaximums[1] = test_P.HILInitialize_AOHigh;
      test_DWork.HILInitialize_AOMaximums[2] = test_P.HILInitialize_AOHigh;
      test_DWork.HILInitialize_AOMaximums[3] = test_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_AOChannels, 4U,
        &test_DWork.HILInitialize_AOMinimums[0],
        &test_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }

    if ((test_P.HILInitialize_AOStart && !is_switching) ||
        (test_P.HILInitialize_AOEnter && is_switching)) {
      test_DWork.HILInitialize_AOVoltages[0] = test_P.HILInitialize_AOInitial;
      test_DWork.HILInitialize_AOVoltages[1] = test_P.HILInitialize_AOInitial;
      test_DWork.HILInitialize_AOVoltages[2] = test_P.HILInitialize_AOInitial;
      test_DWork.HILInitialize_AOVoltages[3] = test_P.HILInitialize_AOInitial;
      result = hil_write_analog(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_AOChannels, 4U,
        &test_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }

    if (test_P.HILInitialize_AOReset) {
      test_DWork.HILInitialize_AOVoltages[0] = test_P.HILInitialize_AOWatchdog;
      test_DWork.HILInitialize_AOVoltages[1] = test_P.HILInitialize_AOWatchdog;
      test_DWork.HILInitialize_AOVoltages[2] = test_P.HILInitialize_AOWatchdog;
      test_DWork.HILInitialize_AOVoltages[3] = test_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (test_DWork.HILInitialize_Card, test_P.HILInitialize_AOChannels, 4U,
         &test_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }

    if ((test_P.HILInitialize_EIPStart && !is_switching) ||
        (test_P.HILInitialize_EIPEnter && is_switching)) {
      test_DWork.HILInitialize_QuadratureModes[0] =
        test_P.HILInitialize_EIQuadrature;
      test_DWork.HILInitialize_QuadratureModes[1] =
        test_P.HILInitialize_EIQuadrature;
      test_DWork.HILInitialize_QuadratureModes[2] =
        test_P.HILInitialize_EIQuadrature;
      test_DWork.HILInitialize_QuadratureModes[3] =
        test_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_EIChannels, 4U, (t_encoder_quadrature_mode *)
        &test_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }

      test_DWork.HILInitialize_FilterFrequency[0] =
        test_P.HILInitialize_EIFrequency;
      test_DWork.HILInitialize_FilterFrequency[1] =
        test_P.HILInitialize_EIFrequency;
      test_DWork.HILInitialize_FilterFrequency[2] =
        test_P.HILInitialize_EIFrequency;
      test_DWork.HILInitialize_FilterFrequency[3] =
        test_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_EIChannels, 4U,
        &test_DWork.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }

    if ((test_P.HILInitialize_EIStart && !is_switching) ||
        (test_P.HILInitialize_EIEnter && is_switching)) {
      test_DWork.HILInitialize_InitialEICounts[0] =
        test_P.HILInitialize_EIInitial;
      test_DWork.HILInitialize_InitialEICounts[1] =
        test_P.HILInitialize_EIInitial;
      test_DWork.HILInitialize_InitialEICounts[2] =
        test_P.HILInitialize_EIInitial;
      test_DWork.HILInitialize_InitialEICounts[3] =
        test_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(test_DWork.HILInitialize_Card,
        test_P.HILInitialize_EIChannels, 4U,
        &test_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(test_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: test/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(test_DWork.HILInitialize_Card,
      test_P.HILReadEncoderTimebase_SamplesI,
      test_P.HILReadEncoderTimebase_Channels, 2,
      &test_DWork.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(test_M, _rt_error_message);
    }
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  test_terminate();
}

RT_MODEL_test *test(void)
{
  test_initialize(1);
  return test_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
