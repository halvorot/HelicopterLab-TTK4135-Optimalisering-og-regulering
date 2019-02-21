/*
 * helicopter_10_3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_10_3".
 *
 * Model version              : 1.186
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Wed Feb 20 14:22:05 2019
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_10_3.h"
#include "helicopter_10_3_private.h"
#include "helicopter_10_3_dt.h"

/* Block signals (auto storage) */
B_helicopter_10_3_T helicopter_10_3_B;

/* Continuous states */
X_helicopter_10_3_T helicopter_10_3_X;

/* Block states (auto storage) */
DW_helicopter_10_3_T helicopter_10_3_DW;

/* Real-time model */
RT_MODEL_helicopter_10_3_T helicopter_10_3_M_;
RT_MODEL_helicopter_10_3_T *const helicopter_10_3_M = &helicopter_10_3_M_;

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
  helicopter_10_3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_10_3_output(void)
{
  /* local block i/o variables */
  real_T rtb_Sum3_o[4];
  real_T rtb_Backgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain1_idx_3;
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
    /* set solver stop time */
    if (!(helicopter_10_3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_10_3_M->solverInfo,
                            ((helicopter_10_3_M->Timing.clockTickH0 + 1) *
        helicopter_10_3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_10_3_M->solverInfo,
                            ((helicopter_10_3_M->Timing.clockTick0 + 1) *
        helicopter_10_3_M->Timing.stepSize0 +
        helicopter_10_3_M->Timing.clockTickH0 *
        helicopter_10_3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_10_3_M)) {
    helicopter_10_3_M->Timing.t[0] = rtsiGetT(&helicopter_10_3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_10_3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_10_3_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_10_3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_10_3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_10_3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_10_3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' */
    helicopter_10_3_B.TravelCounttorad = helicopter_10_3_P.TravelCounttorad_Gain
      * rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    helicopter_10_3_B.Gain = helicopter_10_3_P.Gain_Gain *
      helicopter_10_3_B.TravelCounttorad;

    /* Sum: '<Root>/Sum5' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter_10_3_B.Sum5 = helicopter_10_3_B.Gain +
      helicopter_10_3_P.Constant_Value;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_10_3_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_10_3_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_3_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_3_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_10_3_M->Timing.t[1];
          u[1] = helicopter_10_3_B.Sum5;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_3_M,
                              "Error writing to MAT-file travel.mat");
            return;
          }

          if (((++helicopter_10_3_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
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
    helicopter_10_3_B.PitchCounttorad = helicopter_10_3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S8>/Gain' */
    helicopter_10_3_B.Gain_i = helicopter_10_3_P.Gain_Gain_a *
      helicopter_10_3_B.PitchCounttorad;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helicopter_10_3_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopter_10_3_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_3_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_3_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopter_10_3_M->Timing.t[1];
          u[1] = helicopter_10_3_B.Gain_i;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_3_M,
                              "Error writing to MAT-file pitch.mat");
            return;
          }

          if (((++helicopter_10_3_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitch.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S4>/Elevation: Count to rad' */
    helicopter_10_3_B.ElevationCounttorad =
      helicopter_10_3_P.ElevationCounttorad_Gain * rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S6>/Gain' */
    helicopter_10_3_B.Gain_e = helicopter_10_3_P.Gain_Gain_lv *
      helicopter_10_3_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_10_3_B.Sum = helicopter_10_3_B.Gain_e +
      helicopter_10_3_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S12>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_10_3_B.Gain_d = (helicopter_10_3_P.TravelTransferFcn_C *
    helicopter_10_3_X.TravelTransferFcn_CSTATE +
    helicopter_10_3_P.TravelTransferFcn_D * helicopter_10_3_B.TravelCounttorad) *
    helicopter_10_3_P.Gain_Gain_l;

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_10_3_B.Gain_b = (helicopter_10_3_P.PitchTransferFcn_C *
    helicopter_10_3_X.PitchTransferFcn_CSTATE +
    helicopter_10_3_P.PitchTransferFcn_D * helicopter_10_3_B.PitchCounttorad) *
    helicopter_10_3_P.Gain_Gain_ae;

  /* Gain: '<S7>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_10_3_B.Gain_dg = (helicopter_10_3_P.ElevationTransferFcn_C *
    helicopter_10_3_X.ElevationTransferFcn_CSTATE +
    helicopter_10_3_P.ElevationTransferFcn_D *
    helicopter_10_3_B.ElevationCounttorad) * helicopter_10_3_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1_idx_2 = helicopter_10_3_P.Gain1_Gain * helicopter_10_3_B.Gain_i;
  rtb_Gain1_idx_3 = helicopter_10_3_P.Gain1_Gain * helicopter_10_3_B.Gain_b;

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_10_3_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_3_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_3_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_10_3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[148]) {
      currTimeIndex = 147;
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

    helicopter_10_3_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 149;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 149;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum3_o[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 149;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<S2>/Gain1'
   */
  rtb_Sum3_o[0] = helicopter_10_3_P.Gain1_Gain * helicopter_10_3_B.Sum5 -
    rtb_Sum3_o[0];
  rtb_Sum3_o[1] = helicopter_10_3_P.Gain1_Gain * helicopter_10_3_B.Gain_d -
    rtb_Sum3_o[1];
  rtb_Sum3_o[2] = rtb_Gain1_idx_2 - rtb_Sum3_o[2];
  rtb_Sum3_o[3] = rtb_Gain1_idx_3 - rtb_Sum3_o[3];

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_10_3_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_3_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_3_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_10_3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[148]) {
      currTimeIndex = 147;
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

    helicopter_10_3_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Backgain = pDataValues[currTimeIndex];
        } else {
          rtb_Backgain = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Backgain = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 149;
      }
    }
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<Root>/Gain'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<Root>/Sum4'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  helicopter_10_3_B.Sum1 = (((rtb_Backgain - (((helicopter_10_3_P.K[0] *
    rtb_Sum3_o[0] + helicopter_10_3_P.K[1] * rtb_Sum3_o[1]) +
    helicopter_10_3_P.K[2] * rtb_Sum3_o[2]) + helicopter_10_3_P.K[3] *
    rtb_Sum3_o[3])) - rtb_Gain1_idx_2) * helicopter_10_3_P.K_pp -
    helicopter_10_3_P.K_pd * rtb_Gain1_idx_3) + helicopter_10_3_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_10_3_X.Integrator_CSTATE >=
      helicopter_10_3_P.Integrator_UpperSat) {
    helicopter_10_3_X.Integrator_CSTATE = helicopter_10_3_P.Integrator_UpperSat;
  } else {
    if (helicopter_10_3_X.Integrator_CSTATE <=
        helicopter_10_3_P.Integrator_LowerSat) {
      helicopter_10_3_X.Integrator_CSTATE =
        helicopter_10_3_P.Integrator_LowerSat;
    }
  }

  rtb_Backgain = helicopter_10_3_X.Integrator_CSTATE;

  /* End of Integrator: '<S3>/Integrator' */

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Gain1_idx_2 = helicopter_10_3_P.elevation_ref_Value -
    helicopter_10_3_P.Gain1_Gain * helicopter_10_3_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<S3>/Sum1'
   */
  helicopter_10_3_B.Sum2 = ((helicopter_10_3_P.K_ep * rtb_Gain1_idx_2 +
    rtb_Backgain) - helicopter_10_3_P.Gain1_Gain * helicopter_10_3_B.Gain_dg *
    helicopter_10_3_P.K_ed) + helicopter_10_3_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (helicopter_10_3_B.Sum2 - helicopter_10_3_B.Sum1) *
    helicopter_10_3_P.Backgain_Gain;

  /* Gain: '<S3>/K_ei' */
  helicopter_10_3_B.K_ei = helicopter_10_3_P.K_ei * rtb_Gain1_idx_2;
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_10_3_DW.TimeStampA >= helicopter_10_3_M->Timing.t[0]) &&
      (helicopter_10_3_DW.TimeStampB >= helicopter_10_3_M->Timing.t[0])) {
    rtb_Gain1_idx_2 = 0.0;
  } else {
    rtb_Gain1_idx_2 = helicopter_10_3_DW.TimeStampA;
    lastU = &helicopter_10_3_DW.LastUAtTimeA;
    if (helicopter_10_3_DW.TimeStampA < helicopter_10_3_DW.TimeStampB) {
      if (helicopter_10_3_DW.TimeStampB < helicopter_10_3_M->Timing.t[0]) {
        rtb_Gain1_idx_2 = helicopter_10_3_DW.TimeStampB;
        lastU = &helicopter_10_3_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_10_3_DW.TimeStampA >= helicopter_10_3_M->Timing.t[0]) {
        rtb_Gain1_idx_2 = helicopter_10_3_DW.TimeStampB;
        lastU = &helicopter_10_3_DW.LastUAtTimeB;
      }
    }

    rtb_Gain1_idx_2 = (helicopter_10_3_B.PitchCounttorad - *lastU) /
      (helicopter_10_3_M->Timing.t[0] - rtb_Gain1_idx_2);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S10>/Gain' */
  helicopter_10_3_B.Gain_l = helicopter_10_3_P.Gain_Gain_a1 * rtb_Gain1_idx_2;
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
  }

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_10_3_P.BackmotorSaturation_UpperSat) {
    helicopter_10_3_B.BackmotorSaturation =
      helicopter_10_3_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_3_P.BackmotorSaturation_LowerSat) {
    helicopter_10_3_B.BackmotorSaturation =
      helicopter_10_3_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter_10_3_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Gain1_idx_2 = (helicopter_10_3_B.Sum1 + helicopter_10_3_B.Sum2) *
    helicopter_10_3_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Gain1_idx_2 > helicopter_10_3_P.FrontmotorSaturation_UpperSat) {
    helicopter_10_3_B.FrontmotorSaturation =
      helicopter_10_3_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Gain1_idx_2 < helicopter_10_3_P.FrontmotorSaturation_LowerSat)
  {
    helicopter_10_3_B.FrontmotorSaturation =
      helicopter_10_3_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter_10_3_B.FrontmotorSaturation = rtb_Gain1_idx_2;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_10_3/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_10_3_DW.HILWriteAnalog_Buffer[0] =
        helicopter_10_3_B.FrontmotorSaturation;
      helicopter_10_3_DW.HILWriteAnalog_Buffer[1] =
        helicopter_10_3_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILWriteAnalog_channels, 2,
        &helicopter_10_3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_10_3_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_10_3_DW.TimeStampA == (rtInf)) {
    helicopter_10_3_DW.TimeStampA = helicopter_10_3_M->Timing.t[0];
    lastU = &helicopter_10_3_DW.LastUAtTimeA;
  } else if (helicopter_10_3_DW.TimeStampB == (rtInf)) {
    helicopter_10_3_DW.TimeStampB = helicopter_10_3_M->Timing.t[0];
    lastU = &helicopter_10_3_DW.LastUAtTimeB;
  } else if (helicopter_10_3_DW.TimeStampA < helicopter_10_3_DW.TimeStampB) {
    helicopter_10_3_DW.TimeStampA = helicopter_10_3_M->Timing.t[0];
    lastU = &helicopter_10_3_DW.LastUAtTimeA;
  } else {
    helicopter_10_3_DW.TimeStampB = helicopter_10_3_M->Timing.t[0];
    lastU = &helicopter_10_3_DW.LastUAtTimeB;
  }

  *lastU = helicopter_10_3_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_10_3_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_10_3_M->solverInfo);
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
  if (!(++helicopter_10_3_M->Timing.clockTick0)) {
    ++helicopter_10_3_M->Timing.clockTickH0;
  }

  helicopter_10_3_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_10_3_M->solverInfo);

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
    if (!(++helicopter_10_3_M->Timing.clockTick1)) {
      ++helicopter_10_3_M->Timing.clockTickH1;
    }

    helicopter_10_3_M->Timing.t[1] = helicopter_10_3_M->Timing.clockTick1 *
      helicopter_10_3_M->Timing.stepSize1 +
      helicopter_10_3_M->Timing.clockTickH1 *
      helicopter_10_3_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_10_3_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter_10_3_T *_rtXdot;
  _rtXdot = ((XDot_helicopter_10_3_T *) helicopter_10_3_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_3_P.TravelTransferFcn_A *
    helicopter_10_3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_3_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_3_P.PitchTransferFcn_A *
    helicopter_10_3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_10_3_P.ElevationTransferFcn_A *
    helicopter_10_3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_10_3_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_10_3_X.Integrator_CSTATE <=
          helicopter_10_3_P.Integrator_LowerSat);
  usat = (helicopter_10_3_X.Integrator_CSTATE >=
          helicopter_10_3_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_10_3_B.K_ei > 0.0)) || (usat &&
       (helicopter_10_3_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_10_3_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_10_3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_10_3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_10_3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_10_3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
      return;
    }

    if ((helicopter_10_3_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_10_3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter_10_3_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_10_3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_10_3_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_analog_input_chan, 8U,
        &helicopter_10_3_DW.HILInitialize_AIMinimums[0],
        &helicopter_10_3_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_3_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_10_3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter_10_3_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_10_3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_10_3_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_10_3_DW.HILInitialize_Card,
         helicopter_10_3_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_3_DW.HILInitialize_AOMinimums[0],
         &helicopter_10_3_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_3_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_3_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_analog_output_cha, 8U,
        &helicopter_10_3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_3_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_3_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_10_3_DW.HILInitialize_Card,
         helicopter_10_3_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_3_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_10_3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_10_3_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_10_3_DW.HILInitialize_Card,
         helicopter_10_3_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_10_3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_3_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_10_3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_10_3_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_encoder_channels, 8U,
        &helicopter_10_3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_3_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_10_3_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter_10_3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter_10_3_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &helicopter_10_3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter_10_3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter_10_3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_10_3_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_10_3_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            helicopter_10_3_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_10_3_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_10_3_DW.HILInitialize_Card,
          &helicopter_10_3_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_10_3_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_10_3_DW.HILInitialize_Card,
          &helicopter_10_3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_10_3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_10_3_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_10_3_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_10_3_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_10_3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_10_3_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter_10_3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_10_3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_10_3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_10_3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            helicopter_10_3_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_3_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_3_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_10_3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_3_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_3_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter_10_3_DW.HILInitialize_Card,
        helicopter_10_3_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_3_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_3_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_10_3_DW.HILInitialize_Card,
         helicopter_10_3_P.HILInitialize_pwm_channels, 8U,
         &helicopter_10_3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_10_3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_10_3_DW.HILInitialize_Card,
       helicopter_10_3_P.HILReadEncoderTimebase_samples_,
       helicopter_10_3_P.HILReadEncoderTimebase_channels, 3,
       &helicopter_10_3_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_3_M, "Error creating .mat file travel.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_3_M,
                        "Error writing mat file header to file travel.mat");
      return;
    }

    helicopter_10_3_DW.ToFile_IWORK.Count = 0;
    helicopter_10_3_DW.ToFile_IWORK.Decimation = -1;
    helicopter_10_3_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_3_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_3_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    helicopter_10_3_DW.ToFile1_IWORK.Count = 0;
    helicopter_10_3_DW.ToFile1_IWORK.Decimation = -1;
    helicopter_10_3_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
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
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1378421413625279,
      3.1262155534580049, 3.1033093000299821, 3.0666274151912156,
      3.014453922394225, 2.9456562771176764, 2.8595077632937147,
      2.7555515879654058, 2.6335051104906526, 2.4931956060326308,
      2.3345185760651095, 2.1583782719260478, 1.967800077870473,
      1.7674110445466207, 1.5625810512761342, 1.3586839679386826,
      1.1605920903248916, 0.97235419679771251, 0.79695012325984027,
      0.63643293374959031, 0.49215959796927389, 0.36485729820996016,
      0.25463993267205981, 0.16109623593017897, 0.083400591252192915,
      0.020423624533390465, -0.029167512815941762, -0.066823004653064955,
      -0.094039185304793924, -0.11230169021979586, -0.12304167596519089,
      -0.12760358353335183, -0.12722285379205733, -0.12301203948381055,
      -0.11595384747675898, -0.10689976340781565, -0.096573044536239661,
      -0.085575006872611548, -0.07439367354278649, -0.063413988602610064,
      -0.052928930978585725, -0.043150984592951379, -0.034223531491125954,
      -0.026231833998759242, -0.019213359191285459, -0.013167274288011298,
      -0.0080630053551753456, -0.0038478045493674506, -0.00045331387359379605,
      0.0021988530036483604, 0.0041924638884134014, 0.0056128908698021623,
      0.00654412528516249, 0.0070665002189294621, 0.0072550329904089829,
      0.0071783005100552839, 0.0068977633952542177, 0.0064674596661119122,
      0.0059339951101777073, 0.0053367645211473717, 0.0047083455725129338,
      0.00407501475230339, 0.0034573422992259192, 0.0028708302460222208,
      0.0023265643498006205, 0.001831856775537548, 0.0013908618413420544,
      0.0010051519083085049, 0.00067424460561774167, 0.00039607604483589951,
      0.00016741753288223538, -1.5764411858470821E-5, -0.00015800314738642171,
      -0.00026407916771299986, -0.00033881565345682881, -0.00038691781724583331,
      -0.00041285121080772663, -0.00042075405089002669, -0.00041437869183475541,
      -0.00039705758179327445, -0.00037168935026994556, -0.00034074105498252183,
      -0.000306263038766121, -0.00026991328973278821, -0.00023298864146415987,
      -0.00019646057949526007, -0.00016101382346239433, -0.00012708622092749198,
      -9.4908810282185783E-5, -6.4545177863867934E-5, -3.5929439305404975E-5,
      -8.90230607054183E-6, 1.6755258848342891E-5, 4.129135336461339E-5,
      6.4956154500282393E-5, 8.7979679297890811E-5, 0.00011055569399486009, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909061995, -0.046506351618091045,
      -0.091625013712091127, -0.14672753935506738, -0.20869397118796099,
      -0.27519058110619471, -0.34459405529584691, -0.41582470131323507,
      -0.48818590989901223, -0.56123801783208871, -0.63470811987008446,
      -0.70456121655624582, -0.76231277622230031, -0.801556133295409,
      -0.81931997308194582, -0.815588333349807, -0.79236751045516307,
      -0.75295157410871649, -0.70161629415148907, -0.64206875804099994,
      -0.57709334312126559, -0.5092091990372547, -0.44086946215160139,
      -0.37417478696752343, -0.3107825787119442, -0.25190786687520983,
      -0.19836454939732892, -0.15062196734849279, -0.10886472260691582,
      -0.073050019660007778, -0.0429599429815801, -0.018247630272643759,
      0.0015229189651780508, 0.016843257232987116, 0.028232768028206266,
      0.036216336275773323, 0.041306875486303907, 0.043992150654512459,
      0.04472533331930028, 0.043918739760705663, 0.041940230496097346,
      0.0391117855425374, 0.035709812407301679, 0.031966789969466856,
      0.028073899229895127, 0.024184339613096639, 0.020417075731343815,
      0.016860803223231576, 0.013577962703094618, 0.010608667508968626,
      0.00797444353906016, 0.0056817079255550443, 0.00372493766144131,
      0.0020894997350678905, 0.00075413108591808277, -0.00030692992141479456,
      -0.0011221484592042687, -0.0017212149165692211, -0.0021338582237368227,
      -0.0023889223561213389, -0.0025136757945377519, -0.0025333232808381792,
      -0.002470689812309882, -0.0023460482128147926, -0.0021770635848864031,
      -0.001978830297052289, -0.0017639797367819748, -0.0015428397321341979,
      -0.0013236292107630535, -0.0011126742431273686, -0.00091463404781465653,
      -0.00073272777896282487, -0.00056895494211180349, -0.00042430408130631267,
      -0.00029894594297531589, -0.00019240865515601804, -0.00010373357424757333,
      -3.161136032920026E-5, 2.5501436221085037E-5, 6.9284440165923942E-5,
      0.00010147292609331563, 0.00012379318114969472, 0.00013791206486560338,
      0.00014539899613333137, 0.00014769859307451328, 0.00014611224787559914,
      0.00014178702413146293, 0.00013571041013960944, 0.00012870964258122479,
      0.00012145452967327138, 0.00011446295423385182, 0.00010810853293945258,
      0.00010263025967553888, 9.8144378065081981E-5, 9.4659204542675985E-5,
      9.2094099190433661E-5, 9.0304058787877081E-5, 8.91109587141193E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.10602875205861008, 0.22266037932307312,
      0.31888147181624243, 0.38944360631121494, 0.43795507377648224,
      0.46997264230352059, 0.49051724877498004, 0.50343100141409247,
      0.5114213858593829, 0.51630439857559984, 0.51925862126752032,
      0.49369500885904039, 0.40816596705876151, 0.27735705984392095,
      0.12554803518857219, -0.026373804426941688, -0.16411590764817874,
      -0.27857678423584425, -0.36281815260289835, -0.42085924264294039,
      -0.45922141703380032, -0.47977920385573469, -0.48299915977627905,
      -0.47137249195678615, -0.44803191699491934, -0.41610397764324641,
      -0.37842371849810486, -0.33742633592109811, -0.2951242577726132,
      -0.25312464196251688, -0.21266516986452452, -0.17465718802102473,
      -0.13973069118134337, -0.10827829968414154, -0.080496712382112909,
      -0.056424811263810638, -0.035977986944966393, -0.018978499319992514,
      -0.0051818550552452112, 0.0057006952153475926, 0.013983347843646946,
      0.019990368682992504, 0.024043846827354089, 0.026454253043480883,
      0.027513464961974841, 0.027489921858446679, 0.026625582310723313,
      0.025134375864333869, 0.023201863003346489, 0.020985844389337632,
      0.018617688948044876, 0.016204179667314442, 0.013829704890780047,
      0.011558650651908638, 0.0094378756039130117, 0.0074991739560053847,
      0.0057616532742171458, 0.0042339729232725139, 0.0029164052970051327,
      0.0018026958727821749, 0.00088170965649384718, 0.00013886092934043028,
      -0.00044266943438280119, -0.00088091922171180839, -0.0011943188110467252,
      -0.0014010371685183717, -0.0015184817035754472, -0.00156293309435058,
      -0.0015492962434657839, -0.0014909491426511202, -0.0013996724643236184,
      -0.0012856440340190624, -0.0011574838622158486, -0.0010223370386524668,
      -0.00088598344454119359, -0.000752964861244103, -0.00062672160478955156,
      -0.00050973226282778107, -0.0004036514333149623, -0.00030944155013681591,
      -0.00022749592500501088, -0.00015775103811508138, -9.97868777746857E-5,
      -5.2914770767496413E-5, -1.6252672910833889E-5, 1.1211682003878476E-5,
      3.0569029520228667E-5, 4.2947186894513511E-5, 4.9478751347061E-5,
      5.1276367137421235E-5, 4.9413784960899309E-5, 4.4910622807850562E-5,
      3.8718343149644826E-5, 3.17044979604158E-5, 2.4631875387714795E-5,
      1.8129184956384723E-5, 1.2651321907297628E-5, 8.4323756487127923E-6,
      5.4485883366234339E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823444032,
      0.46652650905785209, 0.38488436997267739, 0.28224853797988991,
      0.1940458698610692, 0.12807027410815355, 0.082178425885837514,
      0.051655010556449617, 0.031961537781161627, 0.019532050864867787,
      0.011816890767682119, -0.10225444963391978, -0.34211616720111537,
      -0.52323562885936226, -0.607236098621395, -0.60768735846205546,
      -0.55096841288494824, -0.45784350635066207, -0.33696547346821637,
      -0.2321643601601682, -0.15344869756343951, -0.082231147287737491,
      -0.012879823682177518, 0.046506671277971791, 0.093362299847467231,
      0.12771175740669177, 0.15072103658056607, 0.16398953030802713,
      0.16920831259393948, 0.16799846324038506, 0.16183788839196955,
      0.15203192737399912, 0.13970598735872544, 0.12580956598880738,
      0.11112634920811448, 0.0962876044732091, 0.081787297275376966,
      0.067997950499895515, 0.05518657705898921, 0.043530201082371212,
      0.033130610513197406, 0.024028083357382237, 0.016213912577446341,
      0.0096416248645071721, 0.0042368476739758449, -9.4172414112660455E-5,
      -0.0034573581908934614, -0.0059648257855577673, -0.0077300514439495264,
      -0.0088640744560354156, -0.009472621765171026, -0.0096540371229217378,
      -0.0094978991061375924, -0.0090842169554856324, -0.0084831001919825032,
      -0.0077548065916305114, -0.0069500827271529566, -0.0061107214037785258,
      -0.0052702705050695258, -0.0044548376968918313, -0.0036839448651533107,
      -0.0029713949086136678, -0.0023261214548929258, -0.001752999149316029,
      -0.0012535983573396662, -0.00082687342988658694, -0.00046977814022830213,
      -0.00017780556310053114, 5.4547403539183268E-5, 0.00023338840325865505,
      0.00036510671331000739, 0.00045611372121822378, 0.00051264068721285582,
      0.00054058729425352739, 0.00054541437644509247, 0.00053207433318836254,
      0.00050497302581820546, 0.00046795736784708192, 0.00042432331805127504,
      0.00037683953271258543, 0.00032778250052722019, 0.00027897954755971805,
      0.00023185664136158275, 0.00018748842802875714, 0.00014664839142665008,
      0.00010985741965884946, 7.7429390065400763E-5, 4.9512629497139368E-5,
      2.6126257810189951E-5, 7.19046316144096E-6, -7.4503287060877113E-6,
      -1.8012648612194989E-5, -2.4769118632822935E-5, -2.805538075691609E-5,
      -2.8290490290804035E-5, -2.6010761725320298E-5, -2.191145219634838E-5,
      -1.6875785034339347E-5, -1.1935149248357434E-5, -8.0237392002931063E-6,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_3_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_3_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_3_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
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
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.52359877559807444, 0.52359877559803447, 0.52359877559798307,
      0.52359877559791523, 0.523598775597823, 0.5235987755976923,
      0.52359877559749723, 0.52359877559718215, 0.5235987755966055,
      0.52359877559526735, 0.52359877558925361, 0.38860546189573814,
      0.10951698887526935, -0.11003833946102214, -0.2769112375529158,
      -0.39790682731646909, -0.47963675127901123, -0.523591909441963,
      -0.52359877534342569, -0.52359877536343258, -0.5235987224145312,
      -0.50343489391626572, -0.46497044043306418, -0.42077345861352533,
      -0.37347862555446426, -0.32522986550994043, -0.27772344682220712,
      -0.23225530276673964, -0.1897701881732447, -0.15091074088283751,
      -0.11606494657763658, -0.08541089068498342, -0.058958016011036223,
      -0.036584388943327419, -0.01806971265142519, -0.0031240162861197671,
      0.0085879009858575144, 0.017426078578606414, 0.023758780967378851,
      0.027949332008985615, 0.030346034333594642, 0.031274796827770422,
      0.031034093821064371, 0.029891891654304274, 0.028084198910718443,
      0.025814923189764531, 0.023256747740391888, 0.020552773751695546,
      0.01781870716826189, 0.01514540140551849, 0.012601598411287867,
      0.010236739517233145, 0.008083744017371523, 0.0061616771427812694,
      0.0044782499569109855, 0.0030321116735972068, 0.0018149100878760919,
      0.00081310836210016322, 9.5565276842168836E-6, -0.00061517602288165647,
      -0.0010816948208518141, -0.0014108848952404623, -0.0016232063484833861,
      -0.0017381600630382564, -0.0017739020793310276, -0.0017469853873323272,
      -0.0016722086841820872, -0.0015625529081204717, -0.0014291879259837974,
      -0.0012815335105175719, -0.0011273605978063496, -0.000972920686000228,
      -0.0008230930629766636, -0.00068154128644839346, -0.00055087195231493533,
      -0.00043279025403042561, -0.00032824814515925631, -0.00023758206462032359,
      -0.00016063817112712338, -9.6883866645734262E-5, -4.5505078677972644E-5,
      -5.4893309923764391E-6, 2.4304922656237168E-5, 4.50918802708431E-5,
      5.8113799538615982E-5, 6.4606933573472025E-5, 6.577652227375353E-5,
      6.2779201128075122E-5, 5.67109984837793E-5, 4.8598837981454204E-5,
      3.9393103171466169E-5, 2.9958323012006157E-5, 2.1058409934228402E-5,
      1.3332266149043414E-5, 7.2554391803702257E-6, 3.0850995699961835E-6,
      7.9190498794152707E-7, -4.0593744199241742E-17, -1.5332144830864872E-17,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_3_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_3_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_3_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_10_3_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_10_3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_10_3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_10_3_X.Integrator_CSTATE = helicopter_10_3_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_10_3_DW.TimeStampA = (rtInf);
  helicopter_10_3_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_10_3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_10_3_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_10_3_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_10_3_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_3_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter_10_3_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter_10_3_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_3_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_10_3_DW.HILInitialize_Card
                         , helicopter_10_3_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter_10_3_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_10_3_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_10_3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_10_3_DW.HILInitialize_Card,
            helicopter_10_3_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs,
            &helicopter_10_3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_10_3_DW.HILInitialize_Card,
            helicopter_10_3_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter_10_3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_10_3_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_10_3_DW.HILInitialize_Card);
    hil_close(helicopter_10_3_DW.HILInitialize_Card);
    helicopter_10_3_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_10_3_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_3_M, "Error closing MAT-file travel.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_3_M,
                          "Error reopening MAT-file travel.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_3_DW.ToFile_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_3_M,
                          "Error writing header for ans to MAT-file travel.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_3_M, "Error closing MAT-file travel.mat");
        return;
      }

      helicopter_10_3_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helicopter_10_3_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_3_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_3_M,
                          "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_3_DW.ToFile1_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_3_M,
                          "Error writing header for ans to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_3_M, "Error closing MAT-file pitch.mat");
        return;
      }

      helicopter_10_3_DW.ToFile1_PWORK.FilePtr = (NULL);
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
  helicopter_10_3_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_10_3_update();
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
  helicopter_10_3_initialize();
}

void MdlTerminate(void)
{
  helicopter_10_3_terminate();
}

/* Registration function */
RT_MODEL_helicopter_10_3_T *helicopter_10_3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_10_3_P.Integrator_UpperSat = rtInf;
  helicopter_10_3_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_10_3_M, 0,
                sizeof(RT_MODEL_helicopter_10_3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_10_3_M->solverInfo,
                          &helicopter_10_3_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_10_3_M->solverInfo, &rtmGetTPtr(helicopter_10_3_M));
    rtsiSetStepSizePtr(&helicopter_10_3_M->solverInfo,
                       &helicopter_10_3_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_10_3_M->solverInfo,
                 &helicopter_10_3_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter_10_3_M->solverInfo, (real_T **)
                         &helicopter_10_3_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter_10_3_M->solverInfo,
      &helicopter_10_3_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_10_3_M->solverInfo,
      &helicopter_10_3_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_10_3_M->solverInfo,
      &helicopter_10_3_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_10_3_M->solverInfo,
      &helicopter_10_3_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_10_3_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_10_3_M)));
    rtsiSetRTModelPtr(&helicopter_10_3_M->solverInfo, helicopter_10_3_M);
  }

  rtsiSetSimTimeStep(&helicopter_10_3_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_10_3_M->ModelData.intgData.f[0] = helicopter_10_3_M->
    ModelData.odeF[0];
  helicopter_10_3_M->ModelData.contStates = ((real_T *) &helicopter_10_3_X);
  rtsiSetSolverData(&helicopter_10_3_M->solverInfo, (void *)
                    &helicopter_10_3_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter_10_3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_10_3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_10_3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_10_3_M->Timing.sampleTimes =
      (&helicopter_10_3_M->Timing.sampleTimesArray[0]);
    helicopter_10_3_M->Timing.offsetTimes =
      (&helicopter_10_3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_10_3_M->Timing.sampleTimes[0] = (0.0);
    helicopter_10_3_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_10_3_M->Timing.offsetTimes[0] = (0.0);
    helicopter_10_3_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_10_3_M, &helicopter_10_3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_10_3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_10_3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_10_3_M, -1);
  helicopter_10_3_M->Timing.stepSize0 = 0.002;
  helicopter_10_3_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_10_3_M->Sizes.checksums[0] = (1612994999U);
  helicopter_10_3_M->Sizes.checksums[1] = (2295405272U);
  helicopter_10_3_M->Sizes.checksums[2] = (2548438609U);
  helicopter_10_3_M->Sizes.checksums[3] = (1695275779U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter_10_3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter_10_3_M->extModeInfo,
      &helicopter_10_3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_10_3_M->extModeInfo,
                        helicopter_10_3_M->Sizes.checksums);
    rteiSetTPtr(helicopter_10_3_M->extModeInfo, rtmGetTPtr(helicopter_10_3_M));
  }

  helicopter_10_3_M->solverInfoPtr = (&helicopter_10_3_M->solverInfo);
  helicopter_10_3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_10_3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_10_3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_10_3_M->ModelData.blockIO = ((void *) &helicopter_10_3_B);

  {
    helicopter_10_3_B.TravelCounttorad = 0.0;
    helicopter_10_3_B.Gain = 0.0;
    helicopter_10_3_B.Sum5 = 0.0;
    helicopter_10_3_B.PitchCounttorad = 0.0;
    helicopter_10_3_B.Gain_i = 0.0;
    helicopter_10_3_B.Gain_d = 0.0;
    helicopter_10_3_B.Gain_b = 0.0;
    helicopter_10_3_B.ElevationCounttorad = 0.0;
    helicopter_10_3_B.Gain_e = 0.0;
    helicopter_10_3_B.Sum = 0.0;
    helicopter_10_3_B.Gain_dg = 0.0;
    helicopter_10_3_B.Sum1 = 0.0;
    helicopter_10_3_B.Sum2 = 0.0;
    helicopter_10_3_B.K_ei = 0.0;
    helicopter_10_3_B.Gain_l = 0.0;
    helicopter_10_3_B.BackmotorSaturation = 0.0;
    helicopter_10_3_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter_10_3_M->ModelData.defaultParam = ((real_T *)&helicopter_10_3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_10_3_X;
    helicopter_10_3_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter_10_3_X, 0,
                  sizeof(X_helicopter_10_3_T));
  }

  /* states (dwork) */
  helicopter_10_3_M->ModelData.dwork = ((void *) &helicopter_10_3_DW);
  (void) memset((void *)&helicopter_10_3_DW, 0,
                sizeof(DW_helicopter_10_3_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_10_3_DW.TimeStampA = 0.0;
  helicopter_10_3_DW.LastUAtTimeA = 0.0;
  helicopter_10_3_DW.TimeStampB = 0.0;
  helicopter_10_3_DW.LastUAtTimeB = 0.0;
  helicopter_10_3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_10_3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_10_3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_10_3_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_10_3_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter_10_3_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_10_3_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_10_3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_10_3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_10_3_M->Sizes.numBlocks = (61);/* Number of blocks */
  helicopter_10_3_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  helicopter_10_3_M->Sizes.numBlockPrms = (146);/* Sum of parameter "widths" */
  return helicopter_10_3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
