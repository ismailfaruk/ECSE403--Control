/*
 * model_sim.c
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
#include "model_sim.h"
#include "model_sim_private.h"
#include "model_sim_dt.h"

/* Block signals (auto storage) */
BlockIO_model_sim model_sim_B;

/* Continuous states */
ContinuousStates_model_sim model_sim_X;

/* Block states (auto storage) */
D_Work_model_sim model_sim_DWork;

/* Real-time model */
RT_MODEL_model_sim model_sim_M_;
RT_MODEL_model_sim *const model_sim_M = &model_sim_M_;

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
  model_sim_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void model_sim_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  if (rtmIsMajorTimeStep(model_sim_M)) {
    /* set solver stop time */
    if (!(model_sim_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&model_sim_M->solverInfo,
                            ((model_sim_M->Timing.clockTickH0 + 1) *
        model_sim_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&model_sim_M->solverInfo,
                            ((model_sim_M->Timing.clockTick0 + 1) *
        model_sim_M->Timing.stepSize0 + model_sim_M->Timing.clockTickH0 *
        model_sim_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model_sim_M)) {
    model_sim_M->Timing.t[0] = rtsiGetT(&model_sim_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(model_sim_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: model_sim/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(model_sim_DWork.HILReadEncoderTimebase_Task,
        1, &model_sim_DWork.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          model_sim_DWork.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          model_sim_DWork.HILReadEncoderTimebase_Buffer[1];
      }
    }

    /* Gain: '<Root>/Angle Gain' */
    model_sim_B.AngleGain = model_sim_P.AngleGain_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<Root>/position Gain' */
    model_sim_B.positionGain = model_sim_P.positionGain_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  model_sim_B.TransferFcn = model_sim_P.TransferFcn_C*
    model_sim_X.TransferFcn_CSTATE;

  /* TransferFcn: '<Root>/Transfer Fcn1' */
  model_sim_B.TransferFcn1 = model_sim_P.TransferFcn1_C*
    model_sim_X.TransferFcn1_CSTATE;

  /* Switch: '<Root>/Switch' incorporates:
   *  Gain: '<Root>/position Gain1'
   *  SignalConversion: '<Root>/TmpSignal ConversionAtposition Gain1Inport1'
   *  Sum: '<Root>/Sum'
   */
  if (model_sim_B.AngleGain >= model_sim_P.Switch_Threshold) {
    model_sim_B.Switch = 0.0 - (((model_sim_P.positionGain1_Gain[0] *
      model_sim_B.positionGain + model_sim_P.positionGain1_Gain[1] *
      model_sim_B.TransferFcn) + model_sim_P.positionGain1_Gain[2] *
      model_sim_B.AngleGain) + model_sim_P.positionGain1_Gain[3] *
      model_sim_B.TransferFcn1);
  } else {
    model_sim_B.Switch = 0.0;
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(model_sim_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: model_sim/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(model_sim_DWork.HILInitialize_Card,
        &model_sim_P.HILWriteAnalog_Channels, 1, &model_sim_B.Switch);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
      }
    }
  }

  /* Derivative: '<Root>/Derivative' */
  {
    real_T t = model_sim_M->Timing.t[0];
    real_T timeStampA = model_sim_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = model_sim_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &model_sim_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      model_sim_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &model_sim_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &model_sim_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      model_sim_B.Derivative = (model_sim_B.positionGain - *lastU++) / deltaT;
    }
  }

  /* Derivative: '<Root>/Derivative1' */
  {
    real_T t = model_sim_M->Timing.t[0];
    real_T timeStampA = model_sim_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = model_sim_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &model_sim_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      model_sim_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &model_sim_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &model_sim_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      model_sim_B.Derivative1 = (model_sim_B.AngleGain - *lastU++) / deltaT;
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void model_sim_update(int_T tid)
{
  /* Update for Derivative: '<Root>/Derivative' */
  {
    real_T timeStampA = model_sim_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = model_sim_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &model_sim_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &model_sim_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &model_sim_DWork.Derivative_RWORK.TimeStampB;
        lastU = &model_sim_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &model_sim_DWork.Derivative_RWORK.TimeStampB;
        lastU = &model_sim_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = model_sim_M->Timing.t[0];
    *lastU++ = model_sim_B.positionGain;
  }

  /* Update for Derivative: '<Root>/Derivative1' */
  {
    real_T timeStampA = model_sim_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = model_sim_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &model_sim_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &model_sim_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &model_sim_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &model_sim_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &model_sim_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &model_sim_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = model_sim_M->Timing.t[0];
    *lastU++ = model_sim_B.AngleGain;
  }

  if (rtmIsMajorTimeStep(model_sim_M)) {
    rt_ertODEUpdateContinuousStates(&model_sim_M->solverInfo);
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
  if (!(++model_sim_M->Timing.clockTick0)) {
    ++model_sim_M->Timing.clockTickH0;
  }

  model_sim_M->Timing.t[0] = rtsiGetSolverStopTime(&model_sim_M->solverInfo);

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
    if (!(++model_sim_M->Timing.clockTick1)) {
      ++model_sim_M->Timing.clockTickH1;
    }

    model_sim_M->Timing.t[1] = model_sim_M->Timing.clockTick1 *
      model_sim_M->Timing.stepSize1 + model_sim_M->Timing.clockTickH1 *
      model_sim_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void model_sim_derivatives(void)
{
  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  {
    ((StateDerivatives_model_sim *) model_sim_M->ModelData.derivs)
      ->TransferFcn_CSTATE = model_sim_B.Derivative;
    ((StateDerivatives_model_sim *) model_sim_M->ModelData.derivs)
      ->TransferFcn_CSTATE += (model_sim_P.TransferFcn_A)*
      model_sim_X.TransferFcn_CSTATE;
  }

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  {
    ((StateDerivatives_model_sim *) model_sim_M->ModelData.derivs)
      ->TransferFcn1_CSTATE = model_sim_B.Derivative1;
    ((StateDerivatives_model_sim *) model_sim_M->ModelData.derivs)
      ->TransferFcn1_CSTATE += (model_sim_P.TransferFcn1_A)*
      model_sim_X.TransferFcn1_CSTATE;
  }
}

/* Model initialize function */
void model_sim_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)model_sim_M, 0,
                sizeof(RT_MODEL_model_sim));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model_sim_M->solverInfo,
                          &model_sim_M->Timing.simTimeStep);
    rtsiSetTPtr(&model_sim_M->solverInfo, &rtmGetTPtr(model_sim_M));
    rtsiSetStepSizePtr(&model_sim_M->solverInfo, &model_sim_M->Timing.stepSize0);
    rtsiSetdXPtr(&model_sim_M->solverInfo, &model_sim_M->ModelData.derivs);
    rtsiSetContStatesPtr(&model_sim_M->solverInfo,
                         &model_sim_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&model_sim_M->solverInfo,
      &model_sim_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&model_sim_M->solverInfo, (&rtmGetErrorStatus
      (model_sim_M)));
    rtsiSetRTModelPtr(&model_sim_M->solverInfo, model_sim_M);
  }

  rtsiSetSimTimeStep(&model_sim_M->solverInfo, MAJOR_TIME_STEP);
  model_sim_M->ModelData.intgData.f[0] = model_sim_M->ModelData.odeF[0];
  model_sim_M->ModelData.contStates = ((real_T *) &model_sim_X);
  rtsiSetSolverData(&model_sim_M->solverInfo, (void *)
                    &model_sim_M->ModelData.intgData);
  rtsiSetSolverName(&model_sim_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = model_sim_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    model_sim_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    model_sim_M->Timing.sampleTimes = (&model_sim_M->Timing.sampleTimesArray[0]);
    model_sim_M->Timing.offsetTimes = (&model_sim_M->Timing.offsetTimesArray[0]);

    /* task periods */
    model_sim_M->Timing.sampleTimes[0] = (0.0);
    model_sim_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    model_sim_M->Timing.offsetTimes[0] = (0.0);
    model_sim_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(model_sim_M, &model_sim_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = model_sim_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    model_sim_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(model_sim_M, -1);
  model_sim_M->Timing.stepSize0 = 0.002;
  model_sim_M->Timing.stepSize1 = 0.002;

  /* external mode info */
  model_sim_M->Sizes.checksums[0] = (2962947803U);
  model_sim_M->Sizes.checksums[1] = (1731344335U);
  model_sim_M->Sizes.checksums[2] = (1414476032U);
  model_sim_M->Sizes.checksums[3] = (2691778764U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    model_sim_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(model_sim_M->extModeInfo,
      &model_sim_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(model_sim_M->extModeInfo, model_sim_M->Sizes.checksums);
    rteiSetTPtr(model_sim_M->extModeInfo, rtmGetTPtr(model_sim_M));
  }

  model_sim_M->solverInfoPtr = (&model_sim_M->solverInfo);
  model_sim_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&model_sim_M->solverInfo, 0.002);
  rtsiSetSolverMode(&model_sim_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  model_sim_M->ModelData.blockIO = ((void *) &model_sim_B);
  (void) memset(((void *) &model_sim_B), 0,
                sizeof(BlockIO_model_sim));

  /* parameters */
  model_sim_M->ModelData.defaultParam = ((real_T *)&model_sim_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &model_sim_X;
    model_sim_M->ModelData.contStates = (x);
    (void) memset((void *)&model_sim_X, 0,
                  sizeof(ContinuousStates_model_sim));
  }

  /* states (dwork) */
  model_sim_M->Work.dwork = ((void *) &model_sim_DWork);
  (void) memset((void *)&model_sim_DWork, 0,
                sizeof(D_Work_model_sim));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    model_sim_M->SpecialInfo.mappingInfo = (&dtInfo);
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
void model_sim_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: model_sim/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(model_sim_DWork.HILInitialize_Card);
    hil_monitor_stop_all(model_sim_DWork.HILInitialize_Card);
    is_switching = false;
    if ((model_sim_P.HILInitialize_AOTerminate && !is_switching) ||
        (model_sim_P.HILInitialize_AOExit && is_switching)) {
      model_sim_DWork.HILInitialize_AOVoltages[0] =
        model_sim_P.HILInitialize_AOFinal;
      model_sim_DWork.HILInitialize_AOVoltages[1] =
        model_sim_P.HILInitialize_AOFinal;
      model_sim_DWork.HILInitialize_AOVoltages[2] =
        model_sim_P.HILInitialize_AOFinal;
      model_sim_DWork.HILInitialize_AOVoltages[3] =
        model_sim_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(model_sim_DWork.HILInitialize_Card,
        model_sim_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &model_sim_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
      }
    }

    hil_task_delete_all(model_sim_DWork.HILInitialize_Card);
    hil_monitor_delete_all(model_sim_DWork.HILInitialize_Card);
    hil_close(model_sim_DWork.HILInitialize_Card);
    model_sim_DWork.HILInitialize_Card = NULL;
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
  model_sim_output(tid);
}

void MdlUpdate(int_T tid)
{
  model_sim_update(tid);
}

void MdlInitializeSizes(void)
{
  model_sim_M->Sizes.numContStates = (2);/* Number of continuous states */
  model_sim_M->Sizes.numY = (0);       /* Number of model outputs */
  model_sim_M->Sizes.numU = (0);       /* Number of model inputs */
  model_sim_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  model_sim_M->Sizes.numSampTimes = (2);/* Number of sample times */
  model_sim_M->Sizes.numBlocks = (18); /* Number of blocks */
  model_sim_M->Sizes.numBlockIO = (7); /* Number of block outputs */
  model_sim_M->Sizes.numBlockPrms = (88);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  model_sim_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  model_sim_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  model_sim_DWork.Derivative_RWORK.TimeStampA = rtInf;
  model_sim_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  model_sim_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  model_sim_DWork.Derivative1_RWORK.TimeStampB = rtInf;
}

void MdlStart(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: model_sim/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &model_sim_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(model_sim_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((model_sim_P.HILInitialize_CKPStart && !is_switching) ||
        (model_sim_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(model_sim_DWork.HILInitialize_Card, (t_clock *)
        model_sim_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        model_sim_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(model_sim_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(model_sim_M, _rt_error_message);
      return;
    }

    if ((model_sim_P.HILInitialize_AIPStart && !is_switching) ||
        (model_sim_P.HILInitialize_AIPEnter && is_switching)) {
      model_sim_DWork.HILInitialize_AIMinimums[0] =
        model_sim_P.HILInitialize_AILow;
      model_sim_DWork.HILInitialize_AIMinimums[1] =
        model_sim_P.HILInitialize_AILow;
      model_sim_DWork.HILInitialize_AIMinimums[2] =
        model_sim_P.HILInitialize_AILow;
      model_sim_DWork.HILInitialize_AIMinimums[3] =
        model_sim_P.HILInitialize_AILow;
      model_sim_DWork.HILInitialize_AIMaximums[0] =
        model_sim_P.HILInitialize_AIHigh;
      model_sim_DWork.HILInitialize_AIMaximums[1] =
        model_sim_P.HILInitialize_AIHigh;
      model_sim_DWork.HILInitialize_AIMaximums[2] =
        model_sim_P.HILInitialize_AIHigh;
      model_sim_DWork.HILInitialize_AIMaximums[3] =
        model_sim_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(model_sim_DWork.HILInitialize_Card,
        model_sim_P.HILInitialize_AIChannels, 4U,
        &model_sim_DWork.HILInitialize_AIMinimums[0],
        &model_sim_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }

    if ((model_sim_P.HILInitialize_AOPStart && !is_switching) ||
        (model_sim_P.HILInitialize_AOPEnter && is_switching)) {
      model_sim_DWork.HILInitialize_AOMinimums[0] =
        model_sim_P.HILInitialize_AOLow;
      model_sim_DWork.HILInitialize_AOMinimums[1] =
        model_sim_P.HILInitialize_AOLow;
      model_sim_DWork.HILInitialize_AOMinimums[2] =
        model_sim_P.HILInitialize_AOLow;
      model_sim_DWork.HILInitialize_AOMinimums[3] =
        model_sim_P.HILInitialize_AOLow;
      model_sim_DWork.HILInitialize_AOMaximums[0] =
        model_sim_P.HILInitialize_AOHigh;
      model_sim_DWork.HILInitialize_AOMaximums[1] =
        model_sim_P.HILInitialize_AOHigh;
      model_sim_DWork.HILInitialize_AOMaximums[2] =
        model_sim_P.HILInitialize_AOHigh;
      model_sim_DWork.HILInitialize_AOMaximums[3] =
        model_sim_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(model_sim_DWork.HILInitialize_Card,
        model_sim_P.HILInitialize_AOChannels, 4U,
        &model_sim_DWork.HILInitialize_AOMinimums[0],
        &model_sim_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }

    if ((model_sim_P.HILInitialize_AOStart && !is_switching) ||
        (model_sim_P.HILInitialize_AOEnter && is_switching)) {
      model_sim_DWork.HILInitialize_AOVoltages[0] =
        model_sim_P.HILInitialize_AOInitial;
      model_sim_DWork.HILInitialize_AOVoltages[1] =
        model_sim_P.HILInitialize_AOInitial;
      model_sim_DWork.HILInitialize_AOVoltages[2] =
        model_sim_P.HILInitialize_AOInitial;
      model_sim_DWork.HILInitialize_AOVoltages[3] =
        model_sim_P.HILInitialize_AOInitial;
      result = hil_write_analog(model_sim_DWork.HILInitialize_Card,
        model_sim_P.HILInitialize_AOChannels, 4U,
        &model_sim_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }

    if (model_sim_P.HILInitialize_AOReset) {
      model_sim_DWork.HILInitialize_AOVoltages[0] =
        model_sim_P.HILInitialize_AOWatchdog;
      model_sim_DWork.HILInitialize_AOVoltages[1] =
        model_sim_P.HILInitialize_AOWatchdog;
      model_sim_DWork.HILInitialize_AOVoltages[2] =
        model_sim_P.HILInitialize_AOWatchdog;
      model_sim_DWork.HILInitialize_AOVoltages[3] =
        model_sim_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (model_sim_DWork.HILInitialize_Card,
         model_sim_P.HILInitialize_AOChannels, 4U,
         &model_sim_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }

    if ((model_sim_P.HILInitialize_EIPStart && !is_switching) ||
        (model_sim_P.HILInitialize_EIPEnter && is_switching)) {
      model_sim_DWork.HILInitialize_QuadratureModes[0] =
        model_sim_P.HILInitialize_EIQuadrature;
      model_sim_DWork.HILInitialize_QuadratureModes[1] =
        model_sim_P.HILInitialize_EIQuadrature;
      model_sim_DWork.HILInitialize_QuadratureModes[2] =
        model_sim_P.HILInitialize_EIQuadrature;
      model_sim_DWork.HILInitialize_QuadratureModes[3] =
        model_sim_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (model_sim_DWork.HILInitialize_Card,
         model_sim_P.HILInitialize_EIChannels, 4U, (t_encoder_quadrature_mode *)
         &model_sim_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }

      model_sim_DWork.HILInitialize_FilterFrequency[0] =
        model_sim_P.HILInitialize_EIFrequency;
      model_sim_DWork.HILInitialize_FilterFrequency[1] =
        model_sim_P.HILInitialize_EIFrequency;
      model_sim_DWork.HILInitialize_FilterFrequency[2] =
        model_sim_P.HILInitialize_EIFrequency;
      model_sim_DWork.HILInitialize_FilterFrequency[3] =
        model_sim_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency
        (model_sim_DWork.HILInitialize_Card,
         model_sim_P.HILInitialize_EIChannels, 4U,
         &model_sim_DWork.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }

    if ((model_sim_P.HILInitialize_EIStart && !is_switching) ||
        (model_sim_P.HILInitialize_EIEnter && is_switching)) {
      model_sim_DWork.HILInitialize_InitialEICounts[0] =
        model_sim_P.HILInitialize_EIInitial;
      model_sim_DWork.HILInitialize_InitialEICounts[1] =
        model_sim_P.HILInitialize_EIInitial;
      model_sim_DWork.HILInitialize_InitialEICounts[2] =
        model_sim_P.HILInitialize_EIInitial;
      model_sim_DWork.HILInitialize_InitialEICounts[3] =
        model_sim_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(model_sim_DWork.HILInitialize_Card,
        model_sim_P.HILInitialize_EIChannels, 4U,
        &model_sim_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_sim_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: model_sim/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(model_sim_DWork.HILInitialize_Card,
      model_sim_P.HILReadEncoderTimebase_SamplesI,
      model_sim_P.HILReadEncoderTimebase_Channels, 2,
      &model_sim_DWork.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(model_sim_M, _rt_error_message);
    }
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  model_sim_terminate();
}

RT_MODEL_model_sim *model_sim(void)
{
  model_sim_initialize(1);
  return model_sim_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
