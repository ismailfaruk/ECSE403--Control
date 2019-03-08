/*
 * model.c
 *
 * Code generation for model "model.mdl".
 *
 * Model version              : 1.57
 * Simulink Coder version : 8.1 (R2011b) 08-Jul-2011
 * C source code generated on : Thu Nov 01 01:21:15 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "model.h"
#include "model_private.h"
#include "model_dt.h"

/* Block signals (auto storage) */
BlockIO_model model_B;

/* Continuous states */
ContinuousStates_model model_X;

/* Block states (auto storage) */
D_Work_model model_DWork;

/* Real-time model */
RT_MODEL_model model_M_;
RT_MODEL_model *const model_M = &model_M_;

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
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  model_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void model_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_Derivative;
  real_T rtb_Add;
  real_T rtb_l;
  if (rtmIsMajorTimeStep(model_M)) {
    /* set solver stop time */
    if (!(model_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&model_M->solverInfo, ((model_M->Timing.clockTickH0
        + 1) * model_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&model_M->solverInfo, ((model_M->Timing.clockTick0 +
        1) * model_M->Timing.stepSize0 + model_M->Timing.clockTickH0 *
        model_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model_M)) {
    model_M->Timing.t[0] = rtsiGetT(&model_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(model_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: model/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(model_DWork.HILReadEncoderTimebase_Task, 1,
        &model_DWork.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          model_DWork.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          model_DWork.HILReadEncoderTimebase_Buffer[1];
      }
    }

    /* Gain: '<Root>/Angle Gain' */
    model_B.AngleGain = model_P.AngleGain_Gain * rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<Root>/position Gain' */
    model_B.positionGain = model_P.positionGain_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* SignalGenerator: '<Root>/Signal Generator' */
  rtb_Add = model_P.SignalGenerator_Frequency * model_M->Timing.t[0];
  if (rtb_Add - floor(rtb_Add) >= 0.5) {
    rtb_Add = model_P.SignalGenerator_Amplitude;
  } else {
    rtb_Add = -model_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Sum: '<Root>/Add' */
  rtb_Add -= model_B.positionGain;

  /* Gain: '<Root>/l' */
  rtb_l = model_P.l_Gain * rtb_Add;

  /* Gain: '<Root>/l1' */
  model_B.l1 = model_P.l1_Gain * rtb_Add;

  /* Derivative: '<Root>/Derivative' */
  {
    real_T t = model_M->Timing.t[0];
    real_T timeStampA = model_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = model_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &model_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &model_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &model_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative = (model_B.l1 - *lastU++) / deltaT;
    }
  }

  /* Sum: '<Root>/Add1' incorporates:
   *  Integrator: '<Root>/Integrator'
   */
  model_B.Add1 = (rtb_l + rtb_Derivative) + model_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(model_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: model/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(model_DWork.HILInitialize_Card,
        &model_P.HILWriteAnalog_Channels, 1, &model_B.Add1);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<Root>/l2' */
  model_B.l2 = model_P.l2_Gain * rtb_Add;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void model_update(int_T tid)
{
  /* Update for Derivative: '<Root>/Derivative' */
  {
    real_T timeStampA = model_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = model_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &model_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &model_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &model_DWork.Derivative_RWORK.TimeStampB;
        lastU = &model_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &model_DWork.Derivative_RWORK.TimeStampB;
        lastU = &model_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = model_M->Timing.t[0];
    *lastU++ = model_B.l1;
  }

  if (rtmIsMajorTimeStep(model_M)) {
    rt_ertODEUpdateContinuousStates(&model_M->solverInfo);
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
  if (!(++model_M->Timing.clockTick0)) {
    ++model_M->Timing.clockTickH0;
  }

  model_M->Timing.t[0] = rtsiGetSolverStopTime(&model_M->solverInfo);

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
    if (!(++model_M->Timing.clockTick1)) {
      ++model_M->Timing.clockTickH1;
    }

    model_M->Timing.t[1] = model_M->Timing.clockTick1 *
      model_M->Timing.stepSize1 + model_M->Timing.clockTickH1 *
      model_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void model_derivatives(void)
{
  /* Derivatives for Integrator: '<Root>/Integrator' */
  ((StateDerivatives_model *) model_M->ModelData.derivs)->Integrator_CSTATE =
    model_B.l2;
}

/* Model initialize function */
void model_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)model_M, 0,
                sizeof(RT_MODEL_model));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model_M->solverInfo, &model_M->Timing.simTimeStep);
    rtsiSetTPtr(&model_M->solverInfo, &rtmGetTPtr(model_M));
    rtsiSetStepSizePtr(&model_M->solverInfo, &model_M->Timing.stepSize0);
    rtsiSetdXPtr(&model_M->solverInfo, &model_M->ModelData.derivs);
    rtsiSetContStatesPtr(&model_M->solverInfo, &model_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&model_M->solverInfo, &model_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&model_M->solverInfo, (&rtmGetErrorStatus(model_M)));
    rtsiSetRTModelPtr(&model_M->solverInfo, model_M);
  }

  rtsiSetSimTimeStep(&model_M->solverInfo, MAJOR_TIME_STEP);
  model_M->ModelData.intgData.f[0] = model_M->ModelData.odeF[0];
  model_M->ModelData.contStates = ((real_T *) &model_X);
  rtsiSetSolverData(&model_M->solverInfo, (void *)&model_M->ModelData.intgData);
  rtsiSetSolverName(&model_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = model_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    model_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    model_M->Timing.sampleTimes = (&model_M->Timing.sampleTimesArray[0]);
    model_M->Timing.offsetTimes = (&model_M->Timing.offsetTimesArray[0]);

    /* task periods */
    model_M->Timing.sampleTimes[0] = (0.0);
    model_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    model_M->Timing.offsetTimes[0] = (0.0);
    model_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(model_M, &model_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = model_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    model_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(model_M, -1);
  model_M->Timing.stepSize0 = 0.002;
  model_M->Timing.stepSize1 = 0.002;

  /* external mode info */
  model_M->Sizes.checksums[0] = (2821683484U);
  model_M->Sizes.checksums[1] = (1597302155U);
  model_M->Sizes.checksums[2] = (2293130819U);
  model_M->Sizes.checksums[3] = (3893563799U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(model_M->extModeInfo,
      &model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(model_M->extModeInfo, model_M->Sizes.checksums);
    rteiSetTPtr(model_M->extModeInfo, rtmGetTPtr(model_M));
  }

  model_M->solverInfoPtr = (&model_M->solverInfo);
  model_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&model_M->solverInfo, 0.002);
  rtsiSetSolverMode(&model_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  model_M->ModelData.blockIO = ((void *) &model_B);
  (void) memset(((void *) &model_B), 0,
                sizeof(BlockIO_model));

  /* parameters */
  model_M->ModelData.defaultParam = ((real_T *)&model_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &model_X;
    model_M->ModelData.contStates = (x);
    (void) memset((void *)&model_X, 0,
                  sizeof(ContinuousStates_model));
  }

  /* states (dwork) */
  model_M->Work.dwork = ((void *) &model_DWork);
  (void) memset((void *)&model_DWork, 0,
                sizeof(D_Work_model));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    model_M->SpecialInfo.mappingInfo = (&dtInfo);
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
void model_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: model/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(model_DWork.HILInitialize_Card);
    hil_monitor_stop_all(model_DWork.HILInitialize_Card);
    is_switching = false;
    if ((model_P.HILInitialize_AOTerminate && !is_switching) ||
        (model_P.HILInitialize_AOExit && is_switching)) {
      model_DWork.HILInitialize_AOVoltages[0] = model_P.HILInitialize_AOFinal;
      model_DWork.HILInitialize_AOVoltages[1] = model_P.HILInitialize_AOFinal;
      model_DWork.HILInitialize_AOVoltages[2] = model_P.HILInitialize_AOFinal;
      model_DWork.HILInitialize_AOVoltages[3] = model_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &model_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
      }
    }

    hil_task_delete_all(model_DWork.HILInitialize_Card);
    hil_monitor_delete_all(model_DWork.HILInitialize_Card);
    hil_close(model_DWork.HILInitialize_Card);
    model_DWork.HILInitialize_Card = NULL;
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
  model_output(tid);
}

void MdlUpdate(int_T tid)
{
  model_update(tid);
}

void MdlInitializeSizes(void)
{
  model_M->Sizes.numContStates = (1);  /* Number of continuous states */
  model_M->Sizes.numY = (0);           /* Number of model outputs */
  model_M->Sizes.numU = (0);           /* Number of model inputs */
  model_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  model_M->Sizes.numSampTimes = (2);   /* Number of sample times */
  model_M->Sizes.numBlocks = (18);     /* Number of blocks */
  model_M->Sizes.numBlockIO = (5);     /* Number of block outputs */
  model_M->Sizes.numBlockPrms = (85);  /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  model_DWork.Derivative_RWORK.TimeStampA = rtInf;
  model_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  model_X.Integrator_CSTATE = model_P.Integrator_IC;
}

void MdlStart(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: model/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &model_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(model_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((model_P.HILInitialize_CKPStart && !is_switching) ||
        (model_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(model_DWork.HILInitialize_Card, (t_clock *)
        model_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        model_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(model_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(model_M, _rt_error_message);
      return;
    }

    if ((model_P.HILInitialize_AIPStart && !is_switching) ||
        (model_P.HILInitialize_AIPEnter && is_switching)) {
      model_DWork.HILInitialize_AIMinimums[0] = model_P.HILInitialize_AILow;
      model_DWork.HILInitialize_AIMinimums[1] = model_P.HILInitialize_AILow;
      model_DWork.HILInitialize_AIMinimums[2] = model_P.HILInitialize_AILow;
      model_DWork.HILInitialize_AIMinimums[3] = model_P.HILInitialize_AILow;
      model_DWork.HILInitialize_AIMaximums[0] = model_P.HILInitialize_AIHigh;
      model_DWork.HILInitialize_AIMaximums[1] = model_P.HILInitialize_AIHigh;
      model_DWork.HILInitialize_AIMaximums[2] = model_P.HILInitialize_AIHigh;
      model_DWork.HILInitialize_AIMaximums[3] = model_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_AIChannels, 4U,
        &model_DWork.HILInitialize_AIMinimums[0],
        &model_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }

    if ((model_P.HILInitialize_AOPStart && !is_switching) ||
        (model_P.HILInitialize_AOPEnter && is_switching)) {
      model_DWork.HILInitialize_AOMinimums[0] = model_P.HILInitialize_AOLow;
      model_DWork.HILInitialize_AOMinimums[1] = model_P.HILInitialize_AOLow;
      model_DWork.HILInitialize_AOMinimums[2] = model_P.HILInitialize_AOLow;
      model_DWork.HILInitialize_AOMinimums[3] = model_P.HILInitialize_AOLow;
      model_DWork.HILInitialize_AOMaximums[0] = model_P.HILInitialize_AOHigh;
      model_DWork.HILInitialize_AOMaximums[1] = model_P.HILInitialize_AOHigh;
      model_DWork.HILInitialize_AOMaximums[2] = model_P.HILInitialize_AOHigh;
      model_DWork.HILInitialize_AOMaximums[3] = model_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_AOChannels, 4U,
        &model_DWork.HILInitialize_AOMinimums[0],
        &model_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }

    if ((model_P.HILInitialize_AOStart && !is_switching) ||
        (model_P.HILInitialize_AOEnter && is_switching)) {
      model_DWork.HILInitialize_AOVoltages[0] = model_P.HILInitialize_AOInitial;
      model_DWork.HILInitialize_AOVoltages[1] = model_P.HILInitialize_AOInitial;
      model_DWork.HILInitialize_AOVoltages[2] = model_P.HILInitialize_AOInitial;
      model_DWork.HILInitialize_AOVoltages[3] = model_P.HILInitialize_AOInitial;
      result = hil_write_analog(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_AOChannels, 4U,
        &model_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }

    if (model_P.HILInitialize_AOReset) {
      model_DWork.HILInitialize_AOVoltages[0] = model_P.HILInitialize_AOWatchdog;
      model_DWork.HILInitialize_AOVoltages[1] = model_P.HILInitialize_AOWatchdog;
      model_DWork.HILInitialize_AOVoltages[2] = model_P.HILInitialize_AOWatchdog;
      model_DWork.HILInitialize_AOVoltages[3] = model_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (model_DWork.HILInitialize_Card, model_P.HILInitialize_AOChannels, 4U,
         &model_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }

    if ((model_P.HILInitialize_EIPStart && !is_switching) ||
        (model_P.HILInitialize_EIPEnter && is_switching)) {
      model_DWork.HILInitialize_QuadratureModes[0] =
        model_P.HILInitialize_EIQuadrature;
      model_DWork.HILInitialize_QuadratureModes[1] =
        model_P.HILInitialize_EIQuadrature;
      model_DWork.HILInitialize_QuadratureModes[2] =
        model_P.HILInitialize_EIQuadrature;
      model_DWork.HILInitialize_QuadratureModes[3] =
        model_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_EIChannels, 4U, (t_encoder_quadrature_mode *)
        &model_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }

      model_DWork.HILInitialize_FilterFrequency[0] =
        model_P.HILInitialize_EIFrequency;
      model_DWork.HILInitialize_FilterFrequency[1] =
        model_P.HILInitialize_EIFrequency;
      model_DWork.HILInitialize_FilterFrequency[2] =
        model_P.HILInitialize_EIFrequency;
      model_DWork.HILInitialize_FilterFrequency[3] =
        model_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_EIChannels, 4U,
        &model_DWork.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }

    if ((model_P.HILInitialize_EIStart && !is_switching) ||
        (model_P.HILInitialize_EIEnter && is_switching)) {
      model_DWork.HILInitialize_InitialEICounts[0] =
        model_P.HILInitialize_EIInitial;
      model_DWork.HILInitialize_InitialEICounts[1] =
        model_P.HILInitialize_EIInitial;
      model_DWork.HILInitialize_InitialEICounts[2] =
        model_P.HILInitialize_EIInitial;
      model_DWork.HILInitialize_InitialEICounts[3] =
        model_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(model_DWork.HILInitialize_Card,
        model_P.HILInitialize_EIChannels, 4U,
        &model_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(model_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: model/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(model_DWork.HILInitialize_Card,
      model_P.HILReadEncoderTimebase_SamplesI,
      model_P.HILReadEncoderTimebase_Channels, 2,
      &model_DWork.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(model_M, _rt_error_message);
    }
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  model_terminate();
}

RT_MODEL_model *model(void)
{
  model_initialize(1);
  return model_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
