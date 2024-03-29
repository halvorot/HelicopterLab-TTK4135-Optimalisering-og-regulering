/*
 * helicopter_10_2.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_10_2".
 *
 * Model version              : 1.178
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
<<<<<<< HEAD
 * C source code generated on : Wed Feb 20 13:23:07 2019
=======
 * C source code generated on : Wed Feb 06 14:36:43 2019
>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_10_2.h"
#include "helicopter_10_2_private.h"
#include "helicopter_10_2_dt.h"

/* Block signals (auto storage) */
B_helicopter_10_2_T helicopter_10_2_B;

/* Continuous states */
X_helicopter_10_2_T helicopter_10_2_X;

/* Block states (auto storage) */
DW_helicopter_10_2_T helicopter_10_2_DW;

/* Real-time model */
RT_MODEL_helicopter_10_2_T helicopter_10_2_M_;
RT_MODEL_helicopter_10_2_T *const helicopter_10_2_M = &helicopter_10_2_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_10_2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_10_2_output(void)
{
  /* local block i/o variables */
  real_T rtb_Derivative;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
    /* set solver stop time */
    if (!(helicopter_10_2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_10_2_M->solverInfo,
                            ((helicopter_10_2_M->Timing.clockTickH0 + 1) *
        helicopter_10_2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_10_2_M->solverInfo,
                            ((helicopter_10_2_M->Timing.clockTick0 + 1) *
        helicopter_10_2_M->Timing.stepSize0 +
        helicopter_10_2_M->Timing.clockTickH0 *
        helicopter_10_2_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_10_2_M)) {
    helicopter_10_2_M->Timing.t[0] = rtsiGetT(&helicopter_10_2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_10_2/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_10_2_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_10_2_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_10_2_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_10_2_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_10_2_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' */
    helicopter_10_2_B.TravelCounttorad = helicopter_10_2_P.TravelCounttorad_Gain
      * rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    helicopter_10_2_B.Gain = helicopter_10_2_P.Gain_Gain *
      helicopter_10_2_B.TravelCounttorad;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_10_2_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_10_2_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_2_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_2_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_10_2_M->Timing.t[1];
          u[1] = helicopter_10_2_B.Gain;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_2_M,
                              "Error writing to MAT-file travel.mat");
            return;
          }

          if (((++helicopter_10_2_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file travel.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_10_2_B.PitchCounttorad = helicopter_10_2_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S8>/Gain' */
    helicopter_10_2_B.Gain_i = helicopter_10_2_P.Gain_Gain_a *
      helicopter_10_2_B.PitchCounttorad;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helicopter_10_2_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopter_10_2_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_2_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_2_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopter_10_2_M->Timing.t[1];
          u[1] = helicopter_10_2_B.Gain_i;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_2_M,
                              "Error writing to MAT-file pitch.mat");
            return;
          }

          if (((++helicopter_10_2_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitch.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_10_2_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_2_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_2_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter_10_2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_10_2_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Derivative = pDataValues[currTimeIndex];
        } else {
          rtb_Derivative = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Derivative = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* Gain: '<S12>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_10_2_B.Gain_d = (helicopter_10_2_P.TravelTransferFcn_C *
    helicopter_10_2_X.TravelTransferFcn_CSTATE +
    helicopter_10_2_P.TravelTransferFcn_D * helicopter_10_2_B.TravelCounttorad) *
    helicopter_10_2_P.Gain_Gain_l;

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_10_2_B.Gain_b = (helicopter_10_2_P.PitchTransferFcn_C *
    helicopter_10_2_X.PitchTransferFcn_CSTATE +
    helicopter_10_2_P.PitchTransferFcn_D * helicopter_10_2_B.PitchCounttorad) *
    helicopter_10_2_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' */
    helicopter_10_2_B.ElevationCounttorad =
      helicopter_10_2_P.ElevationCounttorad_Gain * rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S6>/Gain' */
    helicopter_10_2_B.Gain_e = helicopter_10_2_P.Gain_Gain_lv *
      helicopter_10_2_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_10_2_B.Sum = helicopter_10_2_B.Gain_e +
      helicopter_10_2_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_10_2_B.Gain_dg = (helicopter_10_2_P.ElevationTransferFcn_C *
    helicopter_10_2_X.ElevationTransferFcn_CSTATE +
    helicopter_10_2_P.ElevationTransferFcn_D *
    helicopter_10_2_B.ElevationCounttorad) * helicopter_10_2_P.Gain_Gain_n;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  helicopter_10_2_B.Sum1 = ((rtb_Derivative - helicopter_10_2_P.Gain1_Gain *
    helicopter_10_2_B.Gain_i) * helicopter_10_2_P.K_pp -
    helicopter_10_2_P.Gain1_Gain * helicopter_10_2_B.Gain_b *
    helicopter_10_2_P.K_pd) + helicopter_10_2_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_10_2_X.Integrator_CSTATE >=
      helicopter_10_2_P.Integrator_UpperSat) {
    helicopter_10_2_X.Integrator_CSTATE = helicopter_10_2_P.Integrator_UpperSat;
  } else {
    if (helicopter_10_2_X.Integrator_CSTATE <=
        helicopter_10_2_P.Integrator_LowerSat) {
      helicopter_10_2_X.Integrator_CSTATE =
        helicopter_10_2_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Derivative = helicopter_10_2_P.elevation_ref_Value -
    helicopter_10_2_P.Gain1_Gain * helicopter_10_2_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  helicopter_10_2_B.Sum2 = ((helicopter_10_2_P.K_ep * rtb_Derivative +
    helicopter_10_2_X.Integrator_CSTATE) - helicopter_10_2_P.Gain1_Gain *
    helicopter_10_2_B.Gain_dg * helicopter_10_2_P.K_ed) +
    helicopter_10_2_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  helicopter_10_2_B.K_ei = helicopter_10_2_P.K_ei * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_10_2_DW.TimeStampA >= helicopter_10_2_M->Timing.t[0]) &&
      (helicopter_10_2_DW.TimeStampB >= helicopter_10_2_M->Timing.t[0])) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Backgain = helicopter_10_2_DW.TimeStampA;
    lastU = &helicopter_10_2_DW.LastUAtTimeA;
    if (helicopter_10_2_DW.TimeStampA < helicopter_10_2_DW.TimeStampB) {
      if (helicopter_10_2_DW.TimeStampB < helicopter_10_2_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_2_DW.TimeStampB;
        lastU = &helicopter_10_2_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_10_2_DW.TimeStampA >= helicopter_10_2_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_2_DW.TimeStampB;
        lastU = &helicopter_10_2_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_10_2_B.PitchCounttorad - *lastU) /
      (helicopter_10_2_M->Timing.t[0] - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S10>/Gain' */
  helicopter_10_2_B.Gain_l = helicopter_10_2_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (helicopter_10_2_B.Sum2 - helicopter_10_2_B.Sum1) *
    helicopter_10_2_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_10_2_P.BackmotorSaturation_UpperSat) {
    helicopter_10_2_B.BackmotorSaturation =
      helicopter_10_2_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_2_P.BackmotorSaturation_LowerSat) {
    helicopter_10_2_B.BackmotorSaturation =
      helicopter_10_2_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter_10_2_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Backgain = (helicopter_10_2_B.Sum1 + helicopter_10_2_B.Sum2) *
    helicopter_10_2_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Backgain > helicopter_10_2_P.FrontmotorSaturation_UpperSat) {
    helicopter_10_2_B.FrontmotorSaturation =
      helicopter_10_2_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_2_P.FrontmotorSaturation_LowerSat) {
    helicopter_10_2_B.FrontmotorSaturation =
      helicopter_10_2_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter_10_2_B.FrontmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_10_2/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_10_2_DW.HILWriteAnalog_Buffer[0] =
        helicopter_10_2_B.FrontmotorSaturation;
      helicopter_10_2_DW.HILWriteAnalog_Buffer[1] =
        helicopter_10_2_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILWriteAnalog_channels, 2,
        &helicopter_10_2_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_10_2_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_10_2_DW.TimeStampA == (rtInf)) {
    helicopter_10_2_DW.TimeStampA = helicopter_10_2_M->Timing.t[0];
    lastU = &helicopter_10_2_DW.LastUAtTimeA;
  } else if (helicopter_10_2_DW.TimeStampB == (rtInf)) {
    helicopter_10_2_DW.TimeStampB = helicopter_10_2_M->Timing.t[0];
    lastU = &helicopter_10_2_DW.LastUAtTimeB;
  } else if (helicopter_10_2_DW.TimeStampA < helicopter_10_2_DW.TimeStampB) {
    helicopter_10_2_DW.TimeStampA = helicopter_10_2_M->Timing.t[0];
    lastU = &helicopter_10_2_DW.LastUAtTimeA;
  } else {
    helicopter_10_2_DW.TimeStampB = helicopter_10_2_M->Timing.t[0];
    lastU = &helicopter_10_2_DW.LastUAtTimeB;
  }

  *lastU = helicopter_10_2_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_10_2_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_10_2_M->solverInfo);
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
  if (!(++helicopter_10_2_M->Timing.clockTick0)) {
    ++helicopter_10_2_M->Timing.clockTickH0;
  }

  helicopter_10_2_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_10_2_M->solverInfo);

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
    if (!(++helicopter_10_2_M->Timing.clockTick1)) {
      ++helicopter_10_2_M->Timing.clockTickH1;
    }

    helicopter_10_2_M->Timing.t[1] = helicopter_10_2_M->Timing.clockTick1 *
      helicopter_10_2_M->Timing.stepSize1 +
      helicopter_10_2_M->Timing.clockTickH1 *
      helicopter_10_2_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_10_2_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter_10_2_T *_rtXdot;
  _rtXdot = ((XDot_helicopter_10_2_T *) helicopter_10_2_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_2_P.TravelTransferFcn_A *
    helicopter_10_2_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_2_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_2_P.PitchTransferFcn_A *
    helicopter_10_2_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_2_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_10_2_P.ElevationTransferFcn_A *
    helicopter_10_2_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_10_2_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_10_2_X.Integrator_CSTATE <=
          helicopter_10_2_P.Integrator_LowerSat);
  usat = (helicopter_10_2_X.Integrator_CSTATE >=
          helicopter_10_2_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_10_2_B.K_ei > 0.0)) || (usat &&
       (helicopter_10_2_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_10_2_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_10_2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_10_2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_10_2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_10_2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
      return;
    }

    if ((helicopter_10_2_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_10_2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter_10_2_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_10_2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_10_2_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_analog_input_chan, 8U,
        &helicopter_10_2_DW.HILInitialize_AIMinimums[0],
        &helicopter_10_2_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_2_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_10_2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter_10_2_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_10_2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_10_2_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_10_2_DW.HILInitialize_Card,
         helicopter_10_2_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_2_DW.HILInitialize_AOMinimums[0],
         &helicopter_10_2_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_2_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_2_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_analog_output_cha, 8U,
        &helicopter_10_2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_2_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_2_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_10_2_DW.HILInitialize_Card,
         helicopter_10_2_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_2_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_10_2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_10_2_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_10_2_DW.HILInitialize_Card,
         helicopter_10_2_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_10_2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_2_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_10_2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_10_2_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_encoder_channels, 8U,
        &helicopter_10_2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_2_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_10_2_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter_10_2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter_10_2_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &helicopter_10_2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter_10_2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter_10_2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_10_2_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_10_2_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            helicopter_10_2_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_10_2_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_10_2_DW.HILInitialize_Card,
          &helicopter_10_2_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_10_2_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_10_2_DW.HILInitialize_Card,
          &helicopter_10_2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_10_2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_10_2_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_10_2_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_10_2_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_10_2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_10_2_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter_10_2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_10_2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_10_2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_10_2_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            helicopter_10_2_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_2_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_2_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_10_2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_2_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_2_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter_10_2_DW.HILInitialize_Card,
        helicopter_10_2_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_2_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_2_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_10_2_DW.HILInitialize_Card,
         helicopter_10_2_P.HILInitialize_pwm_channels, 8U,
         &helicopter_10_2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_10_2/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_10_2_DW.HILInitialize_Card,
       helicopter_10_2_P.HILReadEncoderTimebase_samples_,
       helicopter_10_2_P.HILReadEncoderTimebase_channels, 3,
       &helicopter_10_2_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_2_M, "Error creating .mat file travel.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_2_M,
                        "Error writing mat file header to file travel.mat");
      return;
    }

    helicopter_10_2_DW.ToFile_IWORK.Count = 0;
    helicopter_10_2_DW.ToFile_IWORK.Decimation = -1;
    helicopter_10_2_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_2_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_2_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    helicopter_10_2_DW.ToFile1_IWORK.Count = 0;
    helicopter_10_2_DW.ToFile1_IWORK.Decimation = -1;
    helicopter_10_2_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559807444,
      0.52359877559803447, 0.52359877559798307, 0.52359877559791523,
      0.523598775597823, 0.5235987755976923, 0.52359877559749723,
      0.52359877559718215, 0.5235987755966055, 0.52359877559526735,
      0.52359877558925361, 0.38860546189573814, 0.10951698887526935,
      -0.11003833946102214, -0.2769112375529158, -0.39790682731646909,
      -0.47963675127901123, -0.523591909441963, -0.52359877534342569,
      -0.52359877536343258, -0.5235987224145312, -0.50343489391626572,
      -0.46497044043306418, -0.42077345861352533, -0.37347862555446426,
      -0.32522986550994043, -0.27772344682220712, -0.23225530276673964,
      -0.1897701881732447, -0.15091074088283751, -0.11606494657763658,
      -0.08541089068498342, -0.058958016011036223, -0.036584388943327419,
      -0.01806971265142519, -0.0031240162861197671, 0.0085879009858575144,
      0.017426078578606414, 0.023758780967378851, 0.027949332008985615,
      0.030346034333594642, 0.031274796827770422, 0.031034093821064371,
      0.029891891654304274, 0.028084198910718443, 0.025814923189764531,
      0.023256747740391888, 0.020552773751695546, 0.01781870716826189,
      0.01514540140551849, 0.012601598411287867, 0.010236739517233145,
      0.008083744017371523, 0.0061616771427812694, 0.0044782499569109855,
      0.0030321116735972068, 0.0018149100878760919, 0.00081310836210016322,
      9.5565276842168836E-6, -0.00061517602288165647, -0.0010816948208518141,
      -0.0014108848952404623, -0.0016232063484833861, -0.0017381600630382564,
      -0.0017739020793310276, -0.0017469853873323272, -0.0016722086841820872,
      -0.0015625529081204717, -0.0014291879259837974, -0.0012815335105175719,
      -0.0011273605978063496, -0.000972920686000228, -0.0008230930629766636,
      -0.00068154128644839346, -0.00055087195231493533, -0.00043279025403042561,
      -0.00032824814515925631, -0.00023758206462032359, -0.00016063817112712338,
      -9.6883866645734262E-5, -4.5505078677972644E-5, -5.4893309923764391E-6,
      2.4304922656237168E-5, 4.50918802708431E-5, 5.8113799538615982E-5,
      6.4606933573472025E-5, 6.577652227375353E-5, 6.2779201128075122E-5,
      5.67109984837793E-5, 4.8598837981454204E-5, 3.9393103171466169E-5,
      2.9958323012006157E-5, 2.1058409934228402E-5, 1.3332266149043414E-5,
      7.2554391803702257E-6, 3.0850995699961835E-6, 7.9190498794152707E-7,
      -4.0593744199241742E-17, -1.5332144830864872E-17, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

    helicopter_10_2_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_2_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_2_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_10_2_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_10_2_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_10_2_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_10_2_X.Integrator_CSTATE = helicopter_10_2_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_10_2_DW.TimeStampA = (rtInf);
  helicopter_10_2_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_10_2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_10_2_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_10_2_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_10_2_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_2_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter_10_2_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter_10_2_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_2_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_10_2_DW.HILInitialize_Card
                         , helicopter_10_2_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter_10_2_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_10_2_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_10_2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_10_2_DW.HILInitialize_Card,
            helicopter_10_2_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs,
            &helicopter_10_2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_10_2_DW.HILInitialize_Card,
            helicopter_10_2_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter_10_2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_10_2_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_10_2_DW.HILInitialize_Card);
    hil_close(helicopter_10_2_DW.HILInitialize_Card);
    helicopter_10_2_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_10_2_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_2_M, "Error closing MAT-file travel.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_2_M,
                          "Error reopening MAT-file travel.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_2_DW.ToFile_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_2_M,
                          "Error writing header for ans to MAT-file travel.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_2_M, "Error closing MAT-file travel.mat");
        return;
      }

      helicopter_10_2_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helicopter_10_2_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_2_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_2_M,
                          "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_2_DW.ToFile1_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_2_M,
                          "Error writing header for ans to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_2_M, "Error closing MAT-file pitch.mat");
        return;
      }

      helicopter_10_2_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
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
  helicopter_10_2_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_10_2_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_10_2_initialize();
}

void MdlTerminate(void)
{
  helicopter_10_2_terminate();
}

/* Registration function */
RT_MODEL_helicopter_10_2_T *helicopter_10_2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_10_2_P.Integrator_UpperSat = rtInf;
  helicopter_10_2_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_10_2_M, 0,
                sizeof(RT_MODEL_helicopter_10_2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_10_2_M->solverInfo,
                          &helicopter_10_2_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_10_2_M->solverInfo, &rtmGetTPtr(helicopter_10_2_M));
    rtsiSetStepSizePtr(&helicopter_10_2_M->solverInfo,
                       &helicopter_10_2_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_10_2_M->solverInfo,
                 &helicopter_10_2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter_10_2_M->solverInfo, (real_T **)
                         &helicopter_10_2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter_10_2_M->solverInfo,
      &helicopter_10_2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_10_2_M->solverInfo,
      &helicopter_10_2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_10_2_M->solverInfo,
      &helicopter_10_2_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_10_2_M->solverInfo,
      &helicopter_10_2_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_10_2_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_10_2_M)));
    rtsiSetRTModelPtr(&helicopter_10_2_M->solverInfo, helicopter_10_2_M);
  }

  rtsiSetSimTimeStep(&helicopter_10_2_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_10_2_M->ModelData.intgData.f[0] = helicopter_10_2_M->
    ModelData.odeF[0];
  helicopter_10_2_M->ModelData.contStates = ((real_T *) &helicopter_10_2_X);
  rtsiSetSolverData(&helicopter_10_2_M->solverInfo, (void *)
                    &helicopter_10_2_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter_10_2_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_10_2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_10_2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_10_2_M->Timing.sampleTimes =
      (&helicopter_10_2_M->Timing.sampleTimesArray[0]);
    helicopter_10_2_M->Timing.offsetTimes =
      (&helicopter_10_2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_10_2_M->Timing.sampleTimes[0] = (0.0);
    helicopter_10_2_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_10_2_M->Timing.offsetTimes[0] = (0.0);
    helicopter_10_2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_10_2_M, &helicopter_10_2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_10_2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_10_2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_10_2_M, -1);
  helicopter_10_2_M->Timing.stepSize0 = 0.002;
  helicopter_10_2_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_10_2_M->Sizes.checksums[0] = (1281563642U);
  helicopter_10_2_M->Sizes.checksums[1] = (3527427436U);
  helicopter_10_2_M->Sizes.checksums[2] = (3153941571U);
  helicopter_10_2_M->Sizes.checksums[3] = (1627419643U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter_10_2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter_10_2_M->extModeInfo,
      &helicopter_10_2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_10_2_M->extModeInfo,
                        helicopter_10_2_M->Sizes.checksums);
    rteiSetTPtr(helicopter_10_2_M->extModeInfo, rtmGetTPtr(helicopter_10_2_M));
  }

  helicopter_10_2_M->solverInfoPtr = (&helicopter_10_2_M->solverInfo);
  helicopter_10_2_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_10_2_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_10_2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_10_2_M->ModelData.blockIO = ((void *) &helicopter_10_2_B);

  {
    helicopter_10_2_B.TravelCounttorad = 0.0;
    helicopter_10_2_B.Gain = 0.0;
    helicopter_10_2_B.PitchCounttorad = 0.0;
    helicopter_10_2_B.Gain_i = 0.0;
    helicopter_10_2_B.Gain_d = 0.0;
    helicopter_10_2_B.Gain_b = 0.0;
    helicopter_10_2_B.ElevationCounttorad = 0.0;
    helicopter_10_2_B.Gain_e = 0.0;
    helicopter_10_2_B.Sum = 0.0;
    helicopter_10_2_B.Gain_dg = 0.0;
    helicopter_10_2_B.Sum1 = 0.0;
    helicopter_10_2_B.Sum2 = 0.0;
    helicopter_10_2_B.K_ei = 0.0;
    helicopter_10_2_B.Gain_l = 0.0;
    helicopter_10_2_B.BackmotorSaturation = 0.0;
    helicopter_10_2_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter_10_2_M->ModelData.defaultParam = ((real_T *)&helicopter_10_2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_10_2_X;
    helicopter_10_2_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter_10_2_X, 0,
                  sizeof(X_helicopter_10_2_T));
  }

  /* states (dwork) */
  helicopter_10_2_M->ModelData.dwork = ((void *) &helicopter_10_2_DW);
  (void) memset((void *)&helicopter_10_2_DW, 0,
                sizeof(DW_helicopter_10_2_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_2_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_10_2_DW.TimeStampA = 0.0;
  helicopter_10_2_DW.LastUAtTimeA = 0.0;
  helicopter_10_2_DW.TimeStampB = 0.0;
  helicopter_10_2_DW.LastUAtTimeB = 0.0;
  helicopter_10_2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_10_2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_10_2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_10_2_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_10_2_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter_10_2_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_10_2_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_10_2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_10_2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_10_2_M->Sizes.numBlocks = (55);/* Number of blocks */
  helicopter_10_2_M->Sizes.numBlockIO = (16);/* Number of block outputs */
  helicopter_10_2_M->Sizes.numBlockPrms = (141);/* Sum of parameter "widths" */
  return helicopter_10_2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
