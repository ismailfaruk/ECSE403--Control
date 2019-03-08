/*
 * Project_Model_Correct.c
 *
 * Code generation for model "Project_Model_Correct.mdl".
 *
 * Model version              : 1.6
 * Simulink Coder version : 8.1 (R2011b) 08-Jul-2011
 * C source code generated on : Fri Nov 23 11:26:13 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Project_Model_Correct.h"
#include "Project_Model_Correct_private.h"
#include "Project_Model_Correct_dt.h"

/* Block signals (auto storage) */
BlockIO_Project_Model_Correct Project_Model_Correct_B;

/* Continuous states */
ContinuousStates_Project_Model_ Project_Model_Correct_X;

/* Block states (auto storage) */
D_Work_Project_Model_Correct Project_Model_Correct_DWork;

/* Real-time model */
RT_MODEL_Project_Model_Correct Project_Model_Correct_M_;
RT_MODEL_Project_Model_Correct *const Project_Model_Correct_M =
  &Project_Model_Correct_M_;

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
  Project_Model_Correct_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void Project_Model_Correct_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  if (rtmIsMajorTimeStep(Project_Model_Correct_M)) {
    /* set solver stop time */
    if (!(Project_Model_Correct_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Project_Model_Correct_M->solverInfo,
                            ((Project_Model_Correct_M->Timing.clockTickH0 + 1) *
        Project_Model_Correct_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Project_Model_Correct_M->solverInfo,
                            ((Project_Model_Correct_M->Timing.clockTick0 + 1) *
        Project_Model_Correct_M->Timing.stepSize0 +
        Project_Model_Correct_M->Timing.clockTickH0 *
        Project_Model_Correct_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Project_Model_Correct_M)) {
    Project_Model_Correct_M->Timing.t[0] = rtsiGetT
      (&Project_Model_Correct_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Project_Model_Correct_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: Project_Model_Correct/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (Project_Model_Correct_DWork.HILReadEncoderTimebase_Task, 1,
         &Project_Model_Correct_DWork.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          Project_Model_Correct_DWork.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          Project_Model_Correct_DWork.HILReadEncoderTimebase_Buffer[1];
      }
    }

    /* Gain: '<Root>/Angle Gain' */
    Project_Model_Correct_B.AngleGain = Project_Model_Correct_P.AngleGain_Gain *
      rtb_HILReadEncoderTimebase_o2;
  }

  /* TransferFcn: '<Root>/Transfer Fcn1' */
  Project_Model_Correct_B.TransferFcn1 = Project_Model_Correct_P.TransferFcn1_C*
    Project_Model_Correct_X.TransferFcn1_CSTATE;
  if (rtmIsMajorTimeStep(Project_Model_Correct_M)) {
    /* Abs: '<Root>/Abs' */
    Project_Model_Correct_B.Abs = fabs(Project_Model_Correct_B.AngleGain);

    /* Gain: '<Root>/position Gain' */
    Project_Model_Correct_B.positionGain =
      Project_Model_Correct_P.positionGain_Gain * rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  Project_Model_Correct_B.TransferFcn = Project_Model_Correct_P.TransferFcn_C*
    Project_Model_Correct_X.TransferFcn_CSTATE;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/position Gain1'
   *  SignalConversion: '<Root>/TmpSignal ConversionAtposition Gain1Inport1'
   *  Sum: '<Root>/Sum'
   */
  if (Project_Model_Correct_B.Abs >= Project_Model_Correct_P.Switch_Threshold) {
    Project_Model_Correct_B.Switch = Project_Model_Correct_P.Constant_Value;
  } else {
    Project_Model_Correct_B.Switch = Project_Model_Correct_P.Constant_Value -
      (((Project_Model_Correct_P.positionGain1_Gain[0] *
         Project_Model_Correct_B.positionGain +
         Project_Model_Correct_P.positionGain1_Gain[1] *
         Project_Model_Correct_B.TransferFcn) +
        Project_Model_Correct_P.positionGain1_Gain[2] *
        Project_Model_Correct_B.AngleGain) +
       Project_Model_Correct_P.positionGain1_Gain[3] *
       Project_Model_Correct_B.TransferFcn1);
  }

  /* End of Switch: '<Root>/Switch' */
  if (rtmIsMajorTimeStep(Project_Model_Correct_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: Project_Model_Correct/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(Project_Model_Correct_DWork.HILInitialize_Card,
        &Project_Model_Correct_P.HILWriteAnalog_Channels, 1,
        &Project_Model_Correct_B.Switch);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
      }
    }
  }

  /* Derivative: '<Root>/Derivative' */
  {
    real_T t = Project_Model_Correct_M->Timing.t[0];
    real_T timeStampA = Project_Model_Correct_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = Project_Model_Correct_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &Project_Model_Correct_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      Project_Model_Correct_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &Project_Model_Correct_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &Project_Model_Correct_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      Project_Model_Correct_B.Derivative = (Project_Model_Correct_B.positionGain
        - *lastU++) / deltaT;
    }
  }

  /* Derivative: '<Root>/Derivative1' */
  {
    real_T t = Project_Model_Correct_M->Timing.t[0];
    real_T timeStampA = Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &Project_Model_Correct_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      Project_Model_Correct_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &Project_Model_Correct_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &Project_Model_Correct_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      Project_Model_Correct_B.Derivative1 = (Project_Model_Correct_B.AngleGain -
        *lastU++) / deltaT;
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void Project_Model_Correct_update(int_T tid)
{
  /* Update for Derivative: '<Root>/Derivative' */
  {
    real_T timeStampA = Project_Model_Correct_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = Project_Model_Correct_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &Project_Model_Correct_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &Project_Model_Correct_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &Project_Model_Correct_DWork.Derivative_RWORK.TimeStampB;
        lastU = &Project_Model_Correct_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &Project_Model_Correct_DWork.Derivative_RWORK.TimeStampB;
        lastU = &Project_Model_Correct_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = Project_Model_Correct_M->Timing.t[0];
    *lastU++ = Project_Model_Correct_B.positionGain;
  }

  /* Update for Derivative: '<Root>/Derivative1' */
  {
    real_T timeStampA = Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &Project_Model_Correct_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &Project_Model_Correct_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &Project_Model_Correct_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = Project_Model_Correct_M->Timing.t[0];
    *lastU++ = Project_Model_Correct_B.AngleGain;
  }

  if (rtmIsMajorTimeStep(Project_Model_Correct_M)) {
    rt_ertODEUpdateContinuousStates(&Project_Model_Correct_M->solverInfo);
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
  if (!(++Project_Model_Correct_M->Timing.clockTick0)) {
    ++Project_Model_Correct_M->Timing.clockTickH0;
  }

  Project_Model_Correct_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Project_Model_Correct_M->solverInfo);

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
    if (!(++Project_Model_Correct_M->Timing.clockTick1)) {
      ++Project_Model_Correct_M->Timing.clockTickH1;
    }

    Project_Model_Correct_M->Timing.t[1] =
      Project_Model_Correct_M->Timing.clockTick1 *
      Project_Model_Correct_M->Timing.stepSize1 +
      Project_Model_Correct_M->Timing.clockTickH1 *
      Project_Model_Correct_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void Project_Model_Correct_derivatives(void)
{
  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  {
    ((StateDerivatives_Project_Model_ *)
      Project_Model_Correct_M->ModelData.derivs)->TransferFcn1_CSTATE =
      Project_Model_Correct_B.Derivative1;
    ((StateDerivatives_Project_Model_ *)
      Project_Model_Correct_M->ModelData.derivs)->TransferFcn1_CSTATE +=
      (Project_Model_Correct_P.TransferFcn1_A)*
      Project_Model_Correct_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  {
    ((StateDerivatives_Project_Model_ *)
      Project_Model_Correct_M->ModelData.derivs)->TransferFcn_CSTATE =
      Project_Model_Correct_B.Derivative;
    ((StateDerivatives_Project_Model_ *)
      Project_Model_Correct_M->ModelData.derivs)->TransferFcn_CSTATE +=
      (Project_Model_Correct_P.TransferFcn_A)*
      Project_Model_Correct_X.TransferFcn_CSTATE;
  }
}

/* Model initialize function */
void Project_Model_Correct_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Project_Model_Correct_M, 0,
                sizeof(RT_MODEL_Project_Model_Correct));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Project_Model_Correct_M->solverInfo,
                          &Project_Model_Correct_M->Timing.simTimeStep);
    rtsiSetTPtr(&Project_Model_Correct_M->solverInfo, &rtmGetTPtr
                (Project_Model_Correct_M));
    rtsiSetStepSizePtr(&Project_Model_Correct_M->solverInfo,
                       &Project_Model_Correct_M->Timing.stepSize0);
    rtsiSetdXPtr(&Project_Model_Correct_M->solverInfo,
                 &Project_Model_Correct_M->ModelData.derivs);
    rtsiSetContStatesPtr(&Project_Model_Correct_M->solverInfo,
                         &Project_Model_Correct_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&Project_Model_Correct_M->solverInfo,
      &Project_Model_Correct_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&Project_Model_Correct_M->solverInfo,
                          (&rtmGetErrorStatus(Project_Model_Correct_M)));
    rtsiSetRTModelPtr(&Project_Model_Correct_M->solverInfo,
                      Project_Model_Correct_M);
  }

  rtsiSetSimTimeStep(&Project_Model_Correct_M->solverInfo, MAJOR_TIME_STEP);
  Project_Model_Correct_M->ModelData.intgData.f[0] =
    Project_Model_Correct_M->ModelData.odeF[0];
  Project_Model_Correct_M->ModelData.contStates = ((real_T *)
    &Project_Model_Correct_X);
  rtsiSetSolverData(&Project_Model_Correct_M->solverInfo, (void *)
                    &Project_Model_Correct_M->ModelData.intgData);
  rtsiSetSolverName(&Project_Model_Correct_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Project_Model_Correct_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    Project_Model_Correct_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Project_Model_Correct_M->Timing.sampleTimes =
      (&Project_Model_Correct_M->Timing.sampleTimesArray[0]);
    Project_Model_Correct_M->Timing.offsetTimes =
      (&Project_Model_Correct_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Project_Model_Correct_M->Timing.sampleTimes[0] = (0.0);
    Project_Model_Correct_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    Project_Model_Correct_M->Timing.offsetTimes[0] = (0.0);
    Project_Model_Correct_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Project_Model_Correct_M, &Project_Model_Correct_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Project_Model_Correct_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Project_Model_Correct_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Project_Model_Correct_M, -1);
  Project_Model_Correct_M->Timing.stepSize0 = 0.002;
  Project_Model_Correct_M->Timing.stepSize1 = 0.002;

  /* external mode info */
  Project_Model_Correct_M->Sizes.checksums[0] = (4172784586U);
  Project_Model_Correct_M->Sizes.checksums[1] = (2972992165U);
  Project_Model_Correct_M->Sizes.checksums[2] = (2784423793U);
  Project_Model_Correct_M->Sizes.checksums[3] = (2648614442U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    Project_Model_Correct_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Project_Model_Correct_M->extModeInfo,
      &Project_Model_Correct_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Project_Model_Correct_M->extModeInfo,
                        Project_Model_Correct_M->Sizes.checksums);
    rteiSetTPtr(Project_Model_Correct_M->extModeInfo, rtmGetTPtr
                (Project_Model_Correct_M));
  }

  Project_Model_Correct_M->solverInfoPtr = (&Project_Model_Correct_M->solverInfo);
  Project_Model_Correct_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Project_Model_Correct_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Project_Model_Correct_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Project_Model_Correct_M->ModelData.blockIO = ((void *)
    &Project_Model_Correct_B);
  (void) memset(((void *) &Project_Model_Correct_B), 0,
                sizeof(BlockIO_Project_Model_Correct));

  /* parameters */
  Project_Model_Correct_M->ModelData.defaultParam = ((real_T *)
    &Project_Model_Correct_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Project_Model_Correct_X;
    Project_Model_Correct_M->ModelData.contStates = (x);
    (void) memset((void *)&Project_Model_Correct_X, 0,
                  sizeof(ContinuousStates_Project_Model_));
  }

  /* states (dwork) */
  Project_Model_Correct_M->Work.dwork = ((void *) &Project_Model_Correct_DWork);
  (void) memset((void *)&Project_Model_Correct_DWork, 0,
                sizeof(D_Work_Project_Model_Correct));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Project_Model_Correct_M->SpecialInfo.mappingInfo = (&dtInfo);
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
void Project_Model_Correct_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Project_Model_Correct/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(Project_Model_Correct_DWork.HILInitialize_Card);
    hil_monitor_stop_all(Project_Model_Correct_DWork.HILInitialize_Card);
    is_switching = false;
    if ((Project_Model_Correct_P.HILInitialize_AOTerminate && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_AOExit && is_switching)) {
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[0] =
        Project_Model_Correct_P.HILInitialize_AOFinal;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[1] =
        Project_Model_Correct_P.HILInitialize_AOFinal;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[2] =
        Project_Model_Correct_P.HILInitialize_AOFinal;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[3] =
        Project_Model_Correct_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(Project_Model_Correct_DWork.HILInitialize_Card,
        Project_Model_Correct_P.HILInitialize_AOChannels,
        num_final_analog_outputs,
        &Project_Model_Correct_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
      }
    }

    hil_task_delete_all(Project_Model_Correct_DWork.HILInitialize_Card);
    hil_monitor_delete_all(Project_Model_Correct_DWork.HILInitialize_Card);
    hil_close(Project_Model_Correct_DWork.HILInitialize_Card);
    Project_Model_Correct_DWork.HILInitialize_Card = NULL;
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
  Project_Model_Correct_output(tid);
}

void MdlUpdate(int_T tid)
{
  Project_Model_Correct_update(tid);
}

void MdlInitializeSizes(void)
{
  Project_Model_Correct_M->Sizes.numContStates = (2);/* Number of continuous states */
  Project_Model_Correct_M->Sizes.numY = (0);/* Number of model outputs */
  Project_Model_Correct_M->Sizes.numU = (0);/* Number of model inputs */
  Project_Model_Correct_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Project_Model_Correct_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Project_Model_Correct_M->Sizes.numBlocks = (20);/* Number of blocks */
  Project_Model_Correct_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  Project_Model_Correct_M->Sizes.numBlockPrms = (89);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  Project_Model_Correct_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  Project_Model_Correct_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  Project_Model_Correct_DWork.Derivative_RWORK.TimeStampA = rtInf;
  Project_Model_Correct_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  Project_Model_Correct_DWork.Derivative1_RWORK.TimeStampB = rtInf;
}

void MdlStart(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Project_Model_Correct/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &Project_Model_Correct_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((Project_Model_Correct_P.HILInitialize_CKPStart && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(Project_Model_Correct_DWork.HILInitialize_Card,
                                  (t_clock *)
        Project_Model_Correct_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        Project_Model_Correct_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(Project_Model_Correct_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
      return;
    }

    if ((Project_Model_Correct_P.HILInitialize_AIPStart && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_AIPEnter && is_switching)) {
      Project_Model_Correct_DWork.HILInitialize_AIMinimums[0] =
        Project_Model_Correct_P.HILInitialize_AILow;
      Project_Model_Correct_DWork.HILInitialize_AIMinimums[1] =
        Project_Model_Correct_P.HILInitialize_AILow;
      Project_Model_Correct_DWork.HILInitialize_AIMinimums[2] =
        Project_Model_Correct_P.HILInitialize_AILow;
      Project_Model_Correct_DWork.HILInitialize_AIMinimums[3] =
        Project_Model_Correct_P.HILInitialize_AILow;
      Project_Model_Correct_DWork.HILInitialize_AIMaximums[0] =
        Project_Model_Correct_P.HILInitialize_AIHigh;
      Project_Model_Correct_DWork.HILInitialize_AIMaximums[1] =
        Project_Model_Correct_P.HILInitialize_AIHigh;
      Project_Model_Correct_DWork.HILInitialize_AIMaximums[2] =
        Project_Model_Correct_P.HILInitialize_AIHigh;
      Project_Model_Correct_DWork.HILInitialize_AIMaximums[3] =
        Project_Model_Correct_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (Project_Model_Correct_DWork.HILInitialize_Card,
         Project_Model_Correct_P.HILInitialize_AIChannels, 4U,
         &Project_Model_Correct_DWork.HILInitialize_AIMinimums[0],
         &Project_Model_Correct_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }

    if ((Project_Model_Correct_P.HILInitialize_AOPStart && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_AOPEnter && is_switching)) {
      Project_Model_Correct_DWork.HILInitialize_AOMinimums[0] =
        Project_Model_Correct_P.HILInitialize_AOLow;
      Project_Model_Correct_DWork.HILInitialize_AOMinimums[1] =
        Project_Model_Correct_P.HILInitialize_AOLow;
      Project_Model_Correct_DWork.HILInitialize_AOMinimums[2] =
        Project_Model_Correct_P.HILInitialize_AOLow;
      Project_Model_Correct_DWork.HILInitialize_AOMinimums[3] =
        Project_Model_Correct_P.HILInitialize_AOLow;
      Project_Model_Correct_DWork.HILInitialize_AOMaximums[0] =
        Project_Model_Correct_P.HILInitialize_AOHigh;
      Project_Model_Correct_DWork.HILInitialize_AOMaximums[1] =
        Project_Model_Correct_P.HILInitialize_AOHigh;
      Project_Model_Correct_DWork.HILInitialize_AOMaximums[2] =
        Project_Model_Correct_P.HILInitialize_AOHigh;
      Project_Model_Correct_DWork.HILInitialize_AOMaximums[3] =
        Project_Model_Correct_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (Project_Model_Correct_DWork.HILInitialize_Card,
         Project_Model_Correct_P.HILInitialize_AOChannels, 4U,
         &Project_Model_Correct_DWork.HILInitialize_AOMinimums[0],
         &Project_Model_Correct_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }

    if ((Project_Model_Correct_P.HILInitialize_AOStart && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_AOEnter && is_switching)) {
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[0] =
        Project_Model_Correct_P.HILInitialize_AOInitial;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[1] =
        Project_Model_Correct_P.HILInitialize_AOInitial;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[2] =
        Project_Model_Correct_P.HILInitialize_AOInitial;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[3] =
        Project_Model_Correct_P.HILInitialize_AOInitial;
      result = hil_write_analog(Project_Model_Correct_DWork.HILInitialize_Card,
        Project_Model_Correct_P.HILInitialize_AOChannels, 4U,
        &Project_Model_Correct_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }

    if (Project_Model_Correct_P.HILInitialize_AOReset) {
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[0] =
        Project_Model_Correct_P.HILInitialize_AOWatchdog;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[1] =
        Project_Model_Correct_P.HILInitialize_AOWatchdog;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[2] =
        Project_Model_Correct_P.HILInitialize_AOWatchdog;
      Project_Model_Correct_DWork.HILInitialize_AOVoltages[3] =
        Project_Model_Correct_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (Project_Model_Correct_DWork.HILInitialize_Card,
         Project_Model_Correct_P.HILInitialize_AOChannels, 4U,
         &Project_Model_Correct_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }

    if ((Project_Model_Correct_P.HILInitialize_EIPStart && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_EIPEnter && is_switching)) {
      Project_Model_Correct_DWork.HILInitialize_QuadratureModes[0] =
        Project_Model_Correct_P.HILInitialize_EIQuadrature;
      Project_Model_Correct_DWork.HILInitialize_QuadratureModes[1] =
        Project_Model_Correct_P.HILInitialize_EIQuadrature;
      Project_Model_Correct_DWork.HILInitialize_QuadratureModes[2] =
        Project_Model_Correct_P.HILInitialize_EIQuadrature;
      Project_Model_Correct_DWork.HILInitialize_QuadratureModes[3] =
        Project_Model_Correct_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (Project_Model_Correct_DWork.HILInitialize_Card,
         Project_Model_Correct_P.HILInitialize_EIChannels, 4U,
         (t_encoder_quadrature_mode *)
         &Project_Model_Correct_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }

      Project_Model_Correct_DWork.HILInitialize_FilterFrequency[0] =
        Project_Model_Correct_P.HILInitialize_EIFrequency;
      Project_Model_Correct_DWork.HILInitialize_FilterFrequency[1] =
        Project_Model_Correct_P.HILInitialize_EIFrequency;
      Project_Model_Correct_DWork.HILInitialize_FilterFrequency[2] =
        Project_Model_Correct_P.HILInitialize_EIFrequency;
      Project_Model_Correct_DWork.HILInitialize_FilterFrequency[3] =
        Project_Model_Correct_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency
        (Project_Model_Correct_DWork.HILInitialize_Card,
         Project_Model_Correct_P.HILInitialize_EIChannels, 4U,
         &Project_Model_Correct_DWork.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }

    if ((Project_Model_Correct_P.HILInitialize_EIStart && !is_switching) ||
        (Project_Model_Correct_P.HILInitialize_EIEnter && is_switching)) {
      Project_Model_Correct_DWork.HILInitialize_InitialEICounts[0] =
        Project_Model_Correct_P.HILInitialize_EIInitial;
      Project_Model_Correct_DWork.HILInitialize_InitialEICounts[1] =
        Project_Model_Correct_P.HILInitialize_EIInitial;
      Project_Model_Correct_DWork.HILInitialize_InitialEICounts[2] =
        Project_Model_Correct_P.HILInitialize_EIInitial;
      Project_Model_Correct_DWork.HILInitialize_InitialEICounts[3] =
        Project_Model_Correct_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts
        (Project_Model_Correct_DWork.HILInitialize_Card,
         Project_Model_Correct_P.HILInitialize_EIChannels, 4U,
         &Project_Model_Correct_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: Project_Model_Correct/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (Project_Model_Correct_DWork.HILInitialize_Card,
       Project_Model_Correct_P.HILReadEncoderTimebase_SamplesI,
       Project_Model_Correct_P.HILReadEncoderTimebase_Channels, 2,
       &Project_Model_Correct_DWork.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Project_Model_Correct_M, _rt_error_message);
    }
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  Project_Model_Correct_terminate();
}

RT_MODEL_Project_Model_Correct *Project_Model_Correct(void)
{
  Project_Model_Correct_initialize(1);
  return Project_Model_Correct_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
