/*
 * helicopter_10_4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_10_4".
 *
 * Model version              : 1.189
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Wed Feb 20 15:23:36 2019
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_10_4.h"
#include "helicopter_10_4_private.h"
#include "helicopter_10_4_dt.h"

/* Block signals (auto storage) */
B_helicopter_10_4_T helicopter_10_4_B;

/* Continuous states */
X_helicopter_10_4_T helicopter_10_4_X;

/* Block states (auto storage) */
DW_helicopter_10_4_T helicopter_10_4_DW;

/* Real-time model */
RT_MODEL_helicopter_10_4_T helicopter_10_4_M_;
RT_MODEL_helicopter_10_4_T *const helicopter_10_4_M = &helicopter_10_4_M_;

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
  helicopter_10_4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_10_4_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace2[2];
  real_T rtb_Sum3_o[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Backgain;
  real_T rtb_Gain1[6];
  real_T rtb_Sum4[2];
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* set solver stop time */
    if (!(helicopter_10_4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_10_4_M->solverInfo,
                            ((helicopter_10_4_M->Timing.clockTickH0 + 1) *
        helicopter_10_4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_10_4_M->solverInfo,
                            ((helicopter_10_4_M->Timing.clockTick0 + 1) *
        helicopter_10_4_M->Timing.stepSize0 +
        helicopter_10_4_M->Timing.clockTickH0 *
        helicopter_10_4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_10_4_M)) {
    helicopter_10_4_M->Timing.t[0] = rtsiGetT(&helicopter_10_4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_10_4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_10_4_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' */
    helicopter_10_4_B.TravelCounttorad = helicopter_10_4_P.TravelCounttorad_Gain
      * rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    helicopter_10_4_B.Gain = helicopter_10_4_P.Gain_Gain *
      helicopter_10_4_B.TravelCounttorad;

    /* Sum: '<Root>/Sum5' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter_10_4_B.Sum5 = helicopter_10_4_B.Gain +
      helicopter_10_4_P.Constant_Value;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_10_4_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_10_4_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_M->Timing.t[1];
          u[1] = helicopter_10_4_B.Sum5;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_M,
                              "Error writing to MAT-file travel.mat");
            return;
          }

          if (((++helicopter_10_4_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
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
    helicopter_10_4_B.PitchCounttorad = helicopter_10_4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S8>/Gain' */
    helicopter_10_4_B.Gain_i = helicopter_10_4_P.Gain_Gain_a *
      helicopter_10_4_B.PitchCounttorad;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helicopter_10_4_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopter_10_4_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_M->Timing.t[1];
          u[1] = helicopter_10_4_B.Gain_i;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_M,
                              "Error writing to MAT-file pitch.mat");
            return;
          }

          if (((++helicopter_10_4_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
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
    helicopter_10_4_B.ElevationCounttorad =
      helicopter_10_4_P.ElevationCounttorad_Gain * rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S6>/Gain' */
    helicopter_10_4_B.Gain_e = helicopter_10_4_P.Gain_Gain_l *
      helicopter_10_4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_10_4_B.Sum = helicopter_10_4_B.Gain_e +
      helicopter_10_4_P.elavation_offsetdeg_Value;

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helicopter_10_4_DW.ToFile2_IWORK.Decimation % 1) &&
          (helicopter_10_4_DW.ToFile2_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_M->Timing.t[1];
          u[1] = helicopter_10_4_B.Sum;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_M,
                              "Error writing to MAT-file elevation.mat");
            return;
          }

          if (((++helicopter_10_4_DW.ToFile2_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elevation.mat.\n");
          }
        }
      }
    }
  }

  /* Gain: '<S12>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_10_4_B.Gain_d = (helicopter_10_4_P.TravelTransferFcn_C *
    helicopter_10_4_X.TravelTransferFcn_CSTATE +
    helicopter_10_4_P.TravelTransferFcn_D * helicopter_10_4_B.TravelCounttorad) *
    helicopter_10_4_P.Gain_Gain_lu;

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_10_4_B.Gain_b = (helicopter_10_4_P.PitchTransferFcn_C *
    helicopter_10_4_X.PitchTransferFcn_CSTATE +
    helicopter_10_4_P.PitchTransferFcn_D * helicopter_10_4_B.PitchCounttorad) *
    helicopter_10_4_P.Gain_Gain_ae;

  /* Gain: '<S7>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_10_4_B.Gain_dg = (helicopter_10_4_P.ElevationTransferFcn_C *
    helicopter_10_4_X.ElevationTransferFcn_CSTATE +
    helicopter_10_4_P.ElevationTransferFcn_D *
    helicopter_10_4_B.ElevationCounttorad) * helicopter_10_4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1[0] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Sum5;
  rtb_Gain1[1] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_d;
  rtb_Gain1[2] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_i;
  rtb_Gain1[3] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_b;
  rtb_Gain1[4] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Sum;
  rtb_Gain1[5] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_dg;

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_10_4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_10_4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[64]) {
      currTimeIndex = 63;
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

    helicopter_10_4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 65;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 65;
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
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum3_o[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 65;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum3' */
  for (i = 0; i < 6; i++) {
    rtb_Sum3_o[i] = rtb_Gain1[i] - rtb_Sum3_o[i];
  }

  /* End of Sum: '<Root>/Sum3' */

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_10_4_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_4_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_4_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_10_4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[64]) {
      currTimeIndex = 63;
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

    helicopter_10_4_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 65;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 65;
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
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_FromWorkspace2[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 65;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/Gain'
   */
  for (i = 0; i < 2; i++) {
    rtb_Backgain = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Backgain += helicopter_10_4_P.K[(i_0 << 1) + i] * rtb_Sum3_o[i_0];
    }

    rtb_Sum4[i] = rtb_FromWorkspace2[i] - rtb_Backgain;
  }

  /* End of Sum: '<Root>/Sum4' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  helicopter_10_4_B.Sum1 = ((rtb_Sum4[0] - rtb_Gain1[2]) *
    helicopter_10_4_P.K_pp - helicopter_10_4_P.K_pd * rtb_Gain1[3]) +
    helicopter_10_4_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_10_4_X.Integrator_CSTATE >=
      helicopter_10_4_P.Integrator_UpperSat) {
    helicopter_10_4_X.Integrator_CSTATE = helicopter_10_4_P.Integrator_UpperSat;
  } else {
    if (helicopter_10_4_X.Integrator_CSTATE <=
        helicopter_10_4_P.Integrator_LowerSat) {
      helicopter_10_4_X.Integrator_CSTATE =
        helicopter_10_4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Backgain = rtb_Sum4[1] - rtb_Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  helicopter_10_4_B.Sum2 = ((helicopter_10_4_P.K_ep * rtb_Backgain +
    helicopter_10_4_X.Integrator_CSTATE) - helicopter_10_4_P.K_ed * rtb_Gain1[5])
    + helicopter_10_4_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  helicopter_10_4_B.K_ei = helicopter_10_4_P.K_ei * rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_10_4_DW.TimeStampA >= helicopter_10_4_M->Timing.t[0]) &&
      (helicopter_10_4_DW.TimeStampB >= helicopter_10_4_M->Timing.t[0])) {
    rtb_Backgain = 0.0;
  } else {
    rtb_Backgain = helicopter_10_4_DW.TimeStampA;
    lastU = &helicopter_10_4_DW.LastUAtTimeA;
    if (helicopter_10_4_DW.TimeStampA < helicopter_10_4_DW.TimeStampB) {
      if (helicopter_10_4_DW.TimeStampB < helicopter_10_4_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_4_DW.TimeStampB;
        lastU = &helicopter_10_4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_10_4_DW.TimeStampA >= helicopter_10_4_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_4_DW.TimeStampB;
        lastU = &helicopter_10_4_DW.LastUAtTimeB;
      }
    }

    rtb_Backgain = (helicopter_10_4_B.PitchCounttorad - *lastU) /
      (helicopter_10_4_M->Timing.t[0] - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S10>/Gain' */
  helicopter_10_4_B.Gain_l = helicopter_10_4_P.Gain_Gain_a1 * rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (helicopter_10_4_B.Sum2 - helicopter_10_4_B.Sum1) *
    helicopter_10_4_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_10_4_P.BackmotorSaturation_UpperSat) {
    helicopter_10_4_B.BackmotorSaturation =
      helicopter_10_4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_4_P.BackmotorSaturation_LowerSat) {
    helicopter_10_4_B.BackmotorSaturation =
      helicopter_10_4_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter_10_4_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Backgain = (helicopter_10_4_B.Sum1 + helicopter_10_4_B.Sum2) *
    helicopter_10_4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Backgain > helicopter_10_4_P.FrontmotorSaturation_UpperSat) {
    helicopter_10_4_B.FrontmotorSaturation =
      helicopter_10_4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_4_P.FrontmotorSaturation_LowerSat) {
    helicopter_10_4_B.FrontmotorSaturation =
      helicopter_10_4_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter_10_4_B.FrontmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_10_4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_10_4_DW.HILWriteAnalog_Buffer[0] =
        helicopter_10_4_B.FrontmotorSaturation;
      helicopter_10_4_DW.HILWriteAnalog_Buffer[1] =
        helicopter_10_4_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILWriteAnalog_channels, 2,
        &helicopter_10_4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_10_4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_10_4_DW.TimeStampA == (rtInf)) {
    helicopter_10_4_DW.TimeStampA = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeA;
  } else if (helicopter_10_4_DW.TimeStampB == (rtInf)) {
    helicopter_10_4_DW.TimeStampB = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeB;
  } else if (helicopter_10_4_DW.TimeStampA < helicopter_10_4_DW.TimeStampB) {
    helicopter_10_4_DW.TimeStampA = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeA;
  } else {
    helicopter_10_4_DW.TimeStampB = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeB;
  }

  *lastU = helicopter_10_4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_10_4_M->solverInfo);
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
  if (!(++helicopter_10_4_M->Timing.clockTick0)) {
    ++helicopter_10_4_M->Timing.clockTickH0;
  }

  helicopter_10_4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_10_4_M->solverInfo);

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
    if (!(++helicopter_10_4_M->Timing.clockTick1)) {
      ++helicopter_10_4_M->Timing.clockTickH1;
    }

    helicopter_10_4_M->Timing.t[1] = helicopter_10_4_M->Timing.clockTick1 *
      helicopter_10_4_M->Timing.stepSize1 +
      helicopter_10_4_M->Timing.clockTickH1 *
      helicopter_10_4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_10_4_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter_10_4_T *_rtXdot;
  _rtXdot = ((XDot_helicopter_10_4_T *) helicopter_10_4_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_4_P.TravelTransferFcn_A *
    helicopter_10_4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_4_P.PitchTransferFcn_A *
    helicopter_10_4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_10_4_P.ElevationTransferFcn_A *
    helicopter_10_4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_10_4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_10_4_X.Integrator_CSTATE <=
          helicopter_10_4_P.Integrator_LowerSat);
  usat = (helicopter_10_4_X.Integrator_CSTATE >=
          helicopter_10_4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_10_4_B.K_ei > 0.0)) || (usat &&
       (helicopter_10_4_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_10_4_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_10_4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_10_4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_10_4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_10_4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      return;
    }

    if ((helicopter_10_4_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_10_4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter_10_4_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_10_4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_10_4_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_analog_input_chan, 8U,
        &helicopter_10_4_DW.HILInitialize_AIMinimums[0],
        &helicopter_10_4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_10_4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter_10_4_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_10_4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_10_4_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_4_DW.HILInitialize_AOMinimums[0],
         &helicopter_10_4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_4_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_analog_output_cha, 8U,
        &helicopter_10_4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_4_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_4_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_10_4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_10_4_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_10_4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_10_4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_10_4_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_encoder_channels, 8U,
        &helicopter_10_4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_10_4_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter_10_4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter_10_4_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &helicopter_10_4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter_10_4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter_10_4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_10_4_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_10_4_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            helicopter_10_4_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_10_4_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_10_4_DW.HILInitialize_Card,
          &helicopter_10_4_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_10_4_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_10_4_DW.HILInitialize_Card,
          &helicopter_10_4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_10_4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_10_4_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_10_4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_10_4_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_10_4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_10_4_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter_10_4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_10_4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_10_4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_10_4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            helicopter_10_4_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_4_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_10_4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_4_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
         &helicopter_10_4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_10_4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_10_4_DW.HILInitialize_Card,
       helicopter_10_4_P.HILReadEncoderTimebase_samples_,
       helicopter_10_4_P.HILReadEncoderTimebase_channels, 3,
       &helicopter_10_4_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_M, "Error creating .mat file travel.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_M,
                        "Error writing mat file header to file travel.mat");
      return;
    }

    helicopter_10_4_DW.ToFile_IWORK.Count = 0;
    helicopter_10_4_DW.ToFile_IWORK.Decimation = -1;
    helicopter_10_4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    helicopter_10_4_DW.ToFile1_IWORK.Count = 0;
    helicopter_10_4_DW.ToFile1_IWORK.Decimation = -1;
    helicopter_10_4_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevation.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_M,
                        "Error creating .mat file elevation.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_M,
                        "Error writing mat file header to file elevation.mat");
      return;
    }

    helicopter_10_4_DW.ToFile2_IWORK.Count = 0;
    helicopter_10_4_DW.ToFile2_IWORK.Decimation = -1;
    helicopter_10_4_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1378421413625261,
      3.1262155534579983, 3.1033093000299643, 3.0666274151911783,
      3.0144539223941584, 2.9456562771175667, 2.8595077632935446,
      2.7565065765512049, 2.6406645422275412, 2.5177816886732471,
      2.3927816886732471, 2.2677816886732471, 2.1427816886732471,
      2.0177816886732471, 1.8927816886732471, 1.7677816886732471,
      1.6427816886732471, 1.5177816886732471, 1.3927816886732471,
      1.2677816886732471, 1.1427816886732471, 1.0181168662292155,
      0.894711763862496, 0.77385160410815945, 0.65688242305248046,
      0.54497779387676737, 0.438998892133328, 0.33943556271401026,
      0.24640657125374496, 0.15969875848004736, 0.078829291819812852,
      0.0031196231624376456, -0.068226851299052288, -0.13604923485508311,
      -0.20116045765626558, -0.26429002424381215, -0.32604316536652339, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909068425,
      -0.046506351618112118, -0.091625013712135411, -0.14672753935514374,
      -0.20869397118807928, -0.27519058110636674, -0.34459405529608839,
      -0.412004746969359, -0.46336813729465554, -0.49153141421717655, -0.5, -0.5,
      -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.4986592897761265,
      -0.49362040946687852, -0.483440639017346, -0.46787672422271614,
      -0.44761851670285241, -0.42391560697375763, -0.39825331767727085,
      -0.37211596584106121, -0.34683125109479029, -0.32347786664093808,
      -0.30283867462950081, -0.28538589784595975, -0.27128953422412327,
      -0.26044489120473008, -0.25251826635018637, -0.24701256449084474,
      -0.24335408788090676, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.10602875205865553, 0.22266037932317662, 0.31888147181640647,
      0.3894436063114417, 0.43795507377677845, 0.46997264230390068,
      0.49051724877547076, 0.47643302303908575, 0.36301682594840912,
      0.19904728507931926, 0.059852729963550053, -6.8782875603146561E-17,
      -1.8559304144110086E-16, 3.3272426080650173E-18, -1.2097314353791053E-16,
      2.13288826070776E-16, 2.8097470909938314E-16, 2.9646675462986027E-17,
      -6.4413656363019969E-17, 2.8003922466017544E-16, 1.1627446843544837E-16,
      -0.0094756278139887778, -0.035612881560434212, -0.07194672964671299,
      -0.10999980554818237, -0.14317727367080038, -0.1675231132739286,
      -0.1813712597237257, -0.18472882031707794, -0.17870270700728344,
      -0.16505280212032819, -0.1458699265504233, -0.12334956068557713,
      -0.099627714350730312, -0.076645795040223841, -0.05602235710992496,
      -0.038912197986512222, -0.025856715421919918, -0.016671353226924861, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462212,
      0.46652650905808429, 0.38488436997291953, 0.282248537980141,
      0.19404586986134689, 0.1280702741084889, 0.082178425886280382,
      -0.056336902945540078, -0.45366478836270652, -0.65587816347635941,
      -0.5567782204630769, -0.23941091985420049, -4.67240702573489E-16,
      7.5568128597475228E-16, -4.9720156311102759E-16, 1.3370478543537433E-15,
      2.7074355815650956E-16, -1.005312128895913E-15, -3.7624132972933047E-16,
      1.3778115186011507E-15, -6.5505899196999534E-16, -0.037902511255955576,
      -0.10454901498578174, -0.14533539234511514, -0.15221230360587751,
      -0.13270987249047203, -0.097383358412512819, -0.055392585799188467,
      -0.013430242373408931, 0.024104453239177932, 0.054599619547821068,
      0.076731502279619473, 0.0900814634593847, 0.094887385339387315,
      0.091927677242025843, 0.082493751721195552, 0.068440636493650939,
      0.052221930258369229, 0.036741448779980229, 0.024618390589094003, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0041173546935679619,
      0.011597202959495331, 0.021803506018961111, 0.034193873055982517,
      0.048296939879054514, 0.063691611323684338, 0.079987519764756432,
      0.096806179185556909, 0.11376229196056, 0.13044457748487709,
      0.14639570908686375, 0.16109065193992383, 0.17391280983367288,
      0.18412735216038253, 0.19085083071843134, 0.19301644605372842,
      0.19165859748714825, 0.18762430047762671, 0.18160390724696157,
      0.17415697431261745, 0.16573419596429942, 0.15669590609147441,
      0.14732758914395722, 0.13785299516225666, 0.12844503284743589,
      0.11923511034470136, 0.1103207193465187, 0.10177188305801513,
      0.093636490734992084, 0.085944729436764733, 0.078712810667507349,
      0.071945969759267855, 0.065640922344427186, 0.059787953169707586,
      0.054372577467135245, 0.049376846848748761, 0.044780471380365845,
      0.040561678847866711, 0.0366978967899158, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.016469418774271848, 0.029919393063709478,
      0.040825212237863111, 0.049561468148085631, 0.056412267292287981,
      0.06157868577851925, 0.065183633764288415, 0.0672746376832019,
      0.067824451100012367, 0.066729142097268324, 0.063804526407946677,
      0.05877977141224032, 0.051288631574996135, 0.040858169306838631,
      0.026893914232195233, 0.0086624613411882788, -0.0054313942663206669,
      -0.01613718803808617, -0.02408157292266053, -0.029787731737376429,
      -0.033691113393272167, -0.03615315949130006, -0.037473267790068765,
      -0.0378983759268023, -0.037631849259283159, -0.036839690010938092,
      -0.035657563992730575, -0.034195345154014282, -0.032541569292092183,
      -0.030767045192909449, -0.028927675077029529, -0.027067363632957985,
      -0.025220189659362648, -0.023411876698878391, -0.021661502810289369,
      -0.019982922473545942, -0.018385501873531652, -0.016875170129996547,
      -0.015455128231803656, -0.014126451101844411, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.39027542559505118,
      -0.062607563654346984, -0.27728510614620894, -0.24339108036694998,
      -0.027783699868696492, 0.089409633649253223, 9.2184103014679914E-16,
      -8.9271614927958278E-16, 1.715386534429645E-15, 4.8210511743781591E-17,
      -1.0612623889669618E-15, -5.9408151628849489E-17, 1.7770980997283242E-15,
      -1.0432286501503285E-15, -0.0467932237727843, -0.12439353562985934,
      -0.17599475231588624, -0.2055866647349601, -0.21699443597990345,
      -0.21384223908332509, -0.19954054522380923, -0.17726506857453361,
      -0.14995462086382597, -0.12029774102830845, -0.090713151050694121,
      -0.063314143809929752, -0.039846174706659319, -0.021573093144728873,
      -0.0091326723791340554, -0.0023355958778394342, -2.9956794454960986E-7,
      4.6343835605036955E-7, 3.78048568943228E-7, 3.78048568943228E-7, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.26351070038834962, 0.2810772637280895,
      0.29828803373486412, 0.31467814647450815, 0.32966216491854133,
      0.34250563800483486, 0.352290850765438, 0.35788220908345392,
      0.35788308516653139, 0.35057903954170189, 0.33388500932048693,
      0.3052666031853622, 0.26165655733991811, 0.19935778194938819,
      0.1139174058667331, -2.3716694781144495E-7, -1.0136369586959116E-6,
      -1.8313598023003702E-6, -3.12818386274092E-7, -5.3224846979079951E-7,
      -1.1261968759776815E-6, -2.1682891751208177E-7, -1.7478120015943743E-7,
      1.1047434627442752E-6, -1.4878829458319672E-6, 1.4609864507744594E-7,
      2.8909500376736145E-7, 3.5579323976757907E-7, -2.47478784930131E-7,
      -2.0085234298586937E-6, -1.7681825669555098E-6, -9.8776620868046425E-7,
      -1.8602867992317515E-6, -1.781510434641836E-6, -6.022336621167392E-7,
      -7.7268355507192579E-7, -3.8282681987767727E-7, 1.4725118379796253E-7,
      4.6123146590855938E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_4_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_4_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_4_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_10_4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_10_4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_10_4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_10_4_X.Integrator_CSTATE = helicopter_10_4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_10_4_DW.TimeStampA = (rtInf);
  helicopter_10_4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_10_4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_10_4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_10_4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_10_4_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_4_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter_10_4_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_10_4_DW.HILInitialize_Card
                         , helicopter_10_4_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter_10_4_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_10_4_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_10_4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_10_4_DW.HILInitialize_Card,
            helicopter_10_4_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs,
            &helicopter_10_4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_10_4_DW.HILInitialize_Card,
            helicopter_10_4_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter_10_4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_10_4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_10_4_DW.HILInitialize_Card);
    hil_close(helicopter_10_4_DW.HILInitialize_Card);
    helicopter_10_4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_10_4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error closing MAT-file travel.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error reopening MAT-file travel.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_4_DW.ToFile_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error writing header for ans to MAT-file travel.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error closing MAT-file travel.mat");
        return;
      }

      helicopter_10_4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helicopter_10_4_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_4_DW.ToFile1_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error writing header for ans to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error closing MAT-file pitch.mat");
        return;
      }

      helicopter_10_4_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helicopter_10_4_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevation.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error closing MAT-file elevation.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error reopening MAT-file elevation.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_4_DW.ToFile2_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error writing header for ans to MAT-file elevation.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error closing MAT-file elevation.mat");
        return;
      }

      helicopter_10_4_DW.ToFile2_PWORK.FilePtr = (NULL);
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
  helicopter_10_4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_10_4_update();
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
  helicopter_10_4_initialize();
}

void MdlTerminate(void)
{
  helicopter_10_4_terminate();
}

/* Registration function */
RT_MODEL_helicopter_10_4_T *helicopter_10_4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_10_4_P.Integrator_UpperSat = rtInf;
  helicopter_10_4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_10_4_M, 0,
                sizeof(RT_MODEL_helicopter_10_4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_10_4_M->solverInfo,
                          &helicopter_10_4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_10_4_M->solverInfo, &rtmGetTPtr(helicopter_10_4_M));
    rtsiSetStepSizePtr(&helicopter_10_4_M->solverInfo,
                       &helicopter_10_4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_10_4_M->solverInfo,
                 &helicopter_10_4_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter_10_4_M->solverInfo, (real_T **)
                         &helicopter_10_4_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_10_4_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_10_4_M)));
    rtsiSetRTModelPtr(&helicopter_10_4_M->solverInfo, helicopter_10_4_M);
  }

  rtsiSetSimTimeStep(&helicopter_10_4_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_10_4_M->ModelData.intgData.f[0] = helicopter_10_4_M->
    ModelData.odeF[0];
  helicopter_10_4_M->ModelData.contStates = ((real_T *) &helicopter_10_4_X);
  rtsiSetSolverData(&helicopter_10_4_M->solverInfo, (void *)
                    &helicopter_10_4_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter_10_4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_10_4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_10_4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_10_4_M->Timing.sampleTimes =
      (&helicopter_10_4_M->Timing.sampleTimesArray[0]);
    helicopter_10_4_M->Timing.offsetTimes =
      (&helicopter_10_4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_10_4_M->Timing.sampleTimes[0] = (0.0);
    helicopter_10_4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_10_4_M->Timing.offsetTimes[0] = (0.0);
    helicopter_10_4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_10_4_M, &helicopter_10_4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_10_4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_10_4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_10_4_M, -1);
  helicopter_10_4_M->Timing.stepSize0 = 0.002;
  helicopter_10_4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_10_4_M->Sizes.checksums[0] = (3883773850U);
  helicopter_10_4_M->Sizes.checksums[1] = (922118942U);
  helicopter_10_4_M->Sizes.checksums[2] = (3626221485U);
  helicopter_10_4_M->Sizes.checksums[3] = (4244937703U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter_10_4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter_10_4_M->extModeInfo,
      &helicopter_10_4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_10_4_M->extModeInfo,
                        helicopter_10_4_M->Sizes.checksums);
    rteiSetTPtr(helicopter_10_4_M->extModeInfo, rtmGetTPtr(helicopter_10_4_M));
  }

  helicopter_10_4_M->solverInfoPtr = (&helicopter_10_4_M->solverInfo);
  helicopter_10_4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_10_4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_10_4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_10_4_M->ModelData.blockIO = ((void *) &helicopter_10_4_B);

  {
    helicopter_10_4_B.TravelCounttorad = 0.0;
    helicopter_10_4_B.Gain = 0.0;
    helicopter_10_4_B.Sum5 = 0.0;
    helicopter_10_4_B.PitchCounttorad = 0.0;
    helicopter_10_4_B.Gain_i = 0.0;
    helicopter_10_4_B.ElevationCounttorad = 0.0;
    helicopter_10_4_B.Gain_e = 0.0;
    helicopter_10_4_B.Sum = 0.0;
    helicopter_10_4_B.Gain_d = 0.0;
    helicopter_10_4_B.Gain_b = 0.0;
    helicopter_10_4_B.Gain_dg = 0.0;
    helicopter_10_4_B.Sum1 = 0.0;
    helicopter_10_4_B.Sum2 = 0.0;
    helicopter_10_4_B.K_ei = 0.0;
    helicopter_10_4_B.Gain_l = 0.0;
    helicopter_10_4_B.BackmotorSaturation = 0.0;
    helicopter_10_4_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter_10_4_M->ModelData.defaultParam = ((real_T *)&helicopter_10_4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_10_4_X;
    helicopter_10_4_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter_10_4_X, 0,
                  sizeof(X_helicopter_10_4_T));
  }

  /* states (dwork) */
  helicopter_10_4_M->ModelData.dwork = ((void *) &helicopter_10_4_DW);
  (void) memset((void *)&helicopter_10_4_DW, 0,
                sizeof(DW_helicopter_10_4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_10_4_DW.TimeStampA = 0.0;
  helicopter_10_4_DW.LastUAtTimeA = 0.0;
  helicopter_10_4_DW.TimeStampB = 0.0;
  helicopter_10_4_DW.LastUAtTimeB = 0.0;
  helicopter_10_4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_10_4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_10_4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_10_4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_10_4_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter_10_4_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_10_4_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_10_4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_10_4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_10_4_M->Sizes.numBlocks = (61);/* Number of blocks */
  helicopter_10_4_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  helicopter_10_4_M->Sizes.numBlockPrms = (153);/* Sum of parameter "widths" */
  return helicopter_10_4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
