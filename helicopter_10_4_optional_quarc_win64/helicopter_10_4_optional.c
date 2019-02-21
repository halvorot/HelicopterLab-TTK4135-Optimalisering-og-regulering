/*
 * helicopter_10_4_optional.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_10_4_optional".
 *
 * Model version              : 1.191
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Wed Feb 20 15:59:56 2019
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_10_4_optional.h"
#include "helicopter_10_4_optional_private.h"
#include "helicopter_10_4_optional_dt.h"

/* Block signals (auto storage) */
B_helicopter_10_4_optional_T helicopter_10_4_optional_B;

/* Continuous states */
X_helicopter_10_4_optional_T helicopter_10_4_optional_X;

/* Block states (auto storage) */
DW_helicopter_10_4_optional_T helicopter_10_4_optional_DW;

/* Real-time model */
RT_MODEL_helicopter_10_4_opti_T helicopter_10_4_optional_M_;
RT_MODEL_helicopter_10_4_opti_T *const helicopter_10_4_optional_M =
  &helicopter_10_4_optional_M_;

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
  helicopter_10_4_optional_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_10_4_optional_output(void)
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
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
    /* set solver stop time */
    if (!(helicopter_10_4_optional_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_10_4_optional_M->solverInfo,
                            ((helicopter_10_4_optional_M->Timing.clockTickH0 + 1)
        * helicopter_10_4_optional_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_10_4_optional_M->solverInfo,
                            ((helicopter_10_4_optional_M->Timing.clockTick0 + 1)
        * helicopter_10_4_optional_M->Timing.stepSize0 +
        helicopter_10_4_optional_M->Timing.clockTickH0 *
        helicopter_10_4_optional_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_10_4_optional_M)) {
    helicopter_10_4_optional_M->Timing.t[0] = rtsiGetT
      (&helicopter_10_4_optional_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_10_4_optional/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_10_4_optional_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_10_4_optional_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_10_4_optional_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_10_4_optional_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_10_4_optional_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' */
    helicopter_10_4_optional_B.TravelCounttorad =
      helicopter_10_4_optional_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S11>/Gain' */
    helicopter_10_4_optional_B.Gain = helicopter_10_4_optional_P.Gain_Gain *
      helicopter_10_4_optional_B.TravelCounttorad;

    /* Sum: '<Root>/Sum5' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter_10_4_optional_B.Sum5 = helicopter_10_4_optional_B.Gain +
      helicopter_10_4_optional_P.Constant_Value;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_10_4_optional_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_10_4_optional_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_optional_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_optional_M->Timing.t[1];
          u[1] = helicopter_10_4_optional_B.Sum5;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_optional_M,
                              "Error writing to MAT-file travel.mat");
            return;
          }

          if (((++helicopter_10_4_optional_DW.ToFile_IWORK.Count)*2)+1 >=
              100000000) {
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
    helicopter_10_4_optional_B.PitchCounttorad =
      helicopter_10_4_optional_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S8>/Gain' */
    helicopter_10_4_optional_B.Gain_i = helicopter_10_4_optional_P.Gain_Gain_a *
      helicopter_10_4_optional_B.PitchCounttorad;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helicopter_10_4_optional_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopter_10_4_optional_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_optional_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_optional_M->Timing.t[1];
          u[1] = helicopter_10_4_optional_B.Gain_i;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_optional_M,
                              "Error writing to MAT-file pitch.mat");
            return;
          }

          if (((++helicopter_10_4_optional_DW.ToFile1_IWORK.Count)*2)+1 >=
              100000000) {
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
    helicopter_10_4_optional_B.ElevationCounttorad =
      helicopter_10_4_optional_P.ElevationCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S6>/Gain' */
    helicopter_10_4_optional_B.Gain_e = helicopter_10_4_optional_P.Gain_Gain_l *
      helicopter_10_4_optional_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_10_4_optional_B.Sum = helicopter_10_4_optional_B.Gain_e +
      helicopter_10_4_optional_P.elavation_offsetdeg_Value;

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helicopter_10_4_optional_DW.ToFile2_IWORK.Decimation % 1) &&
          (helicopter_10_4_optional_DW.ToFile2_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_optional_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_optional_M->Timing.t[1];
          u[1] = helicopter_10_4_optional_B.Sum;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_optional_M,
                              "Error writing to MAT-file elevation.mat");
            return;
          }

          if (((++helicopter_10_4_optional_DW.ToFile2_IWORK.Count)*2)+1 >=
              100000000) {
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
  helicopter_10_4_optional_B.Gain_d =
    (helicopter_10_4_optional_P.TravelTransferFcn_C *
     helicopter_10_4_optional_X.TravelTransferFcn_CSTATE +
     helicopter_10_4_optional_P.TravelTransferFcn_D *
     helicopter_10_4_optional_B.TravelCounttorad) *
    helicopter_10_4_optional_P.Gain_Gain_lu;
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
    /* ToFile: '<Root>/To File3' */
    {
      if (!(++helicopter_10_4_optional_DW.ToFile3_IWORK.Decimation % 1) &&
          (helicopter_10_4_optional_DW.ToFile3_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile3_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_optional_DW.ToFile3_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_optional_M->Timing.t[1];
          u[1] = helicopter_10_4_optional_B.Gain_d;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_optional_M,
                              "Error writing to MAT-file traveltrate.mat");
            return;
          }

          if (((++helicopter_10_4_optional_DW.ToFile3_IWORK.Count)*2)+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file traveltrate.mat.\n");
          }
        }
      }
    }
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_10_4_optional_B.Gain_b =
    (helicopter_10_4_optional_P.PitchTransferFcn_C *
     helicopter_10_4_optional_X.PitchTransferFcn_CSTATE +
     helicopter_10_4_optional_P.PitchTransferFcn_D *
     helicopter_10_4_optional_B.PitchCounttorad) *
    helicopter_10_4_optional_P.Gain_Gain_ae;

  /* Gain: '<S7>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_10_4_optional_B.Gain_dg =
    (helicopter_10_4_optional_P.ElevationTransferFcn_C *
     helicopter_10_4_optional_X.ElevationTransferFcn_CSTATE +
     helicopter_10_4_optional_P.ElevationTransferFcn_D *
     helicopter_10_4_optional_B.ElevationCounttorad) *
    helicopter_10_4_optional_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1[0] = helicopter_10_4_optional_P.Gain1_Gain *
    helicopter_10_4_optional_B.Sum5;
  rtb_Gain1[1] = helicopter_10_4_optional_P.Gain1_Gain *
    helicopter_10_4_optional_B.Gain_d;
  rtb_Gain1[2] = helicopter_10_4_optional_P.Gain1_Gain *
    helicopter_10_4_optional_B.Gain_i;
  rtb_Gain1[3] = helicopter_10_4_optional_P.Gain1_Gain *
    helicopter_10_4_optional_B.Gain_b;
  rtb_Gain1[4] = helicopter_10_4_optional_P.Gain1_Gain *
    helicopter_10_4_optional_B.Sum;
  rtb_Gain1[5] = helicopter_10_4_optional_P.Gain1_Gain *
    helicopter_10_4_optional_B.Gain_dg;

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_10_4_optional_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_4_optional_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex =
      helicopter_10_4_optional_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_10_4_optional_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[84]) {
      currTimeIndex = 83;
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

    helicopter_10_4_optional_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

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
              pDataValues += 85;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum3_o[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 85;
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
            pDataValues += 85;
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
      helicopter_10_4_optional_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_10_4_optional_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex =
      helicopter_10_4_optional_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_10_4_optional_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[84]) {
      currTimeIndex = 83;
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

    helicopter_10_4_optional_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

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
              pDataValues += 85;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 85;
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
            pDataValues += 85;
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
      rtb_Backgain += helicopter_10_4_optional_P.K[(i_0 << 1) + i] *
        rtb_Sum3_o[i_0];
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
  helicopter_10_4_optional_B.Sum1 = ((rtb_Sum4[0] - rtb_Gain1[2]) *
    helicopter_10_4_optional_P.K_pp - helicopter_10_4_optional_P.K_pd *
    rtb_Gain1[3]) + helicopter_10_4_optional_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_10_4_optional_X.Integrator_CSTATE >=
      helicopter_10_4_optional_P.Integrator_UpperSat) {
    helicopter_10_4_optional_X.Integrator_CSTATE =
      helicopter_10_4_optional_P.Integrator_UpperSat;
  } else {
    if (helicopter_10_4_optional_X.Integrator_CSTATE <=
        helicopter_10_4_optional_P.Integrator_LowerSat) {
      helicopter_10_4_optional_X.Integrator_CSTATE =
        helicopter_10_4_optional_P.Integrator_LowerSat;
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
  helicopter_10_4_optional_B.Sum2 = ((helicopter_10_4_optional_P.K_ep *
    rtb_Backgain + helicopter_10_4_optional_X.Integrator_CSTATE) -
    helicopter_10_4_optional_P.K_ed * rtb_Gain1[5]) +
    helicopter_10_4_optional_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  helicopter_10_4_optional_B.K_ei = helicopter_10_4_optional_P.K_ei *
    rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_10_4_optional_DW.TimeStampA >=
       helicopter_10_4_optional_M->Timing.t[0]) &&
      (helicopter_10_4_optional_DW.TimeStampB >=
       helicopter_10_4_optional_M->Timing.t[0])) {
    rtb_Backgain = 0.0;
  } else {
    rtb_Backgain = helicopter_10_4_optional_DW.TimeStampA;
    lastU = &helicopter_10_4_optional_DW.LastUAtTimeA;
    if (helicopter_10_4_optional_DW.TimeStampA <
        helicopter_10_4_optional_DW.TimeStampB) {
      if (helicopter_10_4_optional_DW.TimeStampB <
          helicopter_10_4_optional_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_4_optional_DW.TimeStampB;
        lastU = &helicopter_10_4_optional_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_10_4_optional_DW.TimeStampA >=
          helicopter_10_4_optional_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_4_optional_DW.TimeStampB;
        lastU = &helicopter_10_4_optional_DW.LastUAtTimeB;
      }
    }

    rtb_Backgain = (helicopter_10_4_optional_B.PitchCounttorad - *lastU) /
      (helicopter_10_4_optional_M->Timing.t[0] - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S10>/Gain' */
  helicopter_10_4_optional_B.Gain_l = helicopter_10_4_optional_P.Gain_Gain_a1 *
    rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (helicopter_10_4_optional_B.Sum2 -
                  helicopter_10_4_optional_B.Sum1) *
    helicopter_10_4_optional_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_10_4_optional_P.BackmotorSaturation_UpperSat) {
    helicopter_10_4_optional_B.BackmotorSaturation =
      helicopter_10_4_optional_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain <
             helicopter_10_4_optional_P.BackmotorSaturation_LowerSat) {
    helicopter_10_4_optional_B.BackmotorSaturation =
      helicopter_10_4_optional_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter_10_4_optional_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Backgain = (helicopter_10_4_optional_B.Sum1 +
                  helicopter_10_4_optional_B.Sum2) *
    helicopter_10_4_optional_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Backgain > helicopter_10_4_optional_P.FrontmotorSaturation_UpperSat) {
    helicopter_10_4_optional_B.FrontmotorSaturation =
      helicopter_10_4_optional_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Backgain <
             helicopter_10_4_optional_P.FrontmotorSaturation_LowerSat) {
    helicopter_10_4_optional_B.FrontmotorSaturation =
      helicopter_10_4_optional_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter_10_4_optional_B.FrontmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_10_4_optional/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_10_4_optional_DW.HILWriteAnalog_Buffer[0] =
        helicopter_10_4_optional_B.FrontmotorSaturation;
      helicopter_10_4_optional_DW.HILWriteAnalog_Buffer[1] =
        helicopter_10_4_optional_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_10_4_optional_DW.HILInitialize_Card,
        helicopter_10_4_optional_P.HILWriteAnalog_channels, 2,
        &helicopter_10_4_optional_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_10_4_optional_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_10_4_optional_DW.TimeStampA == (rtInf)) {
    helicopter_10_4_optional_DW.TimeStampA =
      helicopter_10_4_optional_M->Timing.t[0];
    lastU = &helicopter_10_4_optional_DW.LastUAtTimeA;
  } else if (helicopter_10_4_optional_DW.TimeStampB == (rtInf)) {
    helicopter_10_4_optional_DW.TimeStampB =
      helicopter_10_4_optional_M->Timing.t[0];
    lastU = &helicopter_10_4_optional_DW.LastUAtTimeB;
  } else if (helicopter_10_4_optional_DW.TimeStampA <
             helicopter_10_4_optional_DW.TimeStampB) {
    helicopter_10_4_optional_DW.TimeStampA =
      helicopter_10_4_optional_M->Timing.t[0];
    lastU = &helicopter_10_4_optional_DW.LastUAtTimeA;
  } else {
    helicopter_10_4_optional_DW.TimeStampB =
      helicopter_10_4_optional_M->Timing.t[0];
    lastU = &helicopter_10_4_optional_DW.LastUAtTimeB;
  }

  *lastU = helicopter_10_4_optional_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_10_4_optional_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_10_4_optional_M->solverInfo);
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
  if (!(++helicopter_10_4_optional_M->Timing.clockTick0)) {
    ++helicopter_10_4_optional_M->Timing.clockTickH0;
  }

  helicopter_10_4_optional_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_10_4_optional_M->solverInfo);

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
    if (!(++helicopter_10_4_optional_M->Timing.clockTick1)) {
      ++helicopter_10_4_optional_M->Timing.clockTickH1;
    }

    helicopter_10_4_optional_M->Timing.t[1] =
      helicopter_10_4_optional_M->Timing.clockTick1 *
      helicopter_10_4_optional_M->Timing.stepSize1 +
      helicopter_10_4_optional_M->Timing.clockTickH1 *
      helicopter_10_4_optional_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_10_4_optional_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter_10_4_optional_T *_rtXdot;
  _rtXdot = ((XDot_helicopter_10_4_optional_T *)
             helicopter_10_4_optional_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE +=
    helicopter_10_4_optional_P.TravelTransferFcn_A *
    helicopter_10_4_optional_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE +=
    helicopter_10_4_optional_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE +=
    helicopter_10_4_optional_P.PitchTransferFcn_A *
    helicopter_10_4_optional_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_4_optional_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_10_4_optional_P.ElevationTransferFcn_A *
    helicopter_10_4_optional_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_10_4_optional_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_10_4_optional_X.Integrator_CSTATE <=
          helicopter_10_4_optional_P.Integrator_LowerSat);
  usat = (helicopter_10_4_optional_X.Integrator_CSTATE >=
          helicopter_10_4_optional_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_10_4_optional_B.K_ei > 0.0)) ||
      (usat && (helicopter_10_4_optional_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_10_4_optional_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_10_4_optional_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_4_optional/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &helicopter_10_4_optional_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (helicopter_10_4_optional_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_10_4_optional_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
      return;
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_analog_input_ &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_analog_inpu_m &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &helicopter_10_4_optional_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] =
            helicopter_10_4_optional_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &helicopter_10_4_optional_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] =
            helicopter_10_4_optional_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_analog_input_chan, 8U,
         &helicopter_10_4_optional_DW.HILInitialize_AIMinimums[0],
         &helicopter_10_4_optional_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_analog_output &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_analog_outp_b &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &helicopter_10_4_optional_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] =
            helicopter_10_4_optional_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &helicopter_10_4_optional_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] =
            helicopter_10_4_optional_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_4_optional_DW.HILInitialize_AOMinimums[0],
         &helicopter_10_4_optional_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_analog_outp_e &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_analog_outp_j &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            helicopter_10_4_optional_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter_10_4_optional_DW.HILInitialize_Card,
        helicopter_10_4_optional_P.HILInitialize_analog_output_cha, 8U,
        &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_4_optional_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            helicopter_10_4_optional_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_encoder_param &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_encoder_par_m &&
         is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_10_4_optional_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            helicopter_10_4_optional_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_10_4_optional_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_encoder_count &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_encoder_cou_k &&
         is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_10_4_optional_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_10_4_optional_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_encoder_channels, 8U,
         &helicopter_10_4_optional_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_pwm_params_at &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_pwm_params__f &&
         is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_4_optional_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter_10_4_optional_DW.HILInitialize_Card,
        helicopter_10_4_optional_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter_10_4_optional_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter_10_4_optional_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &helicopter_10_4_optional_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter_10_4_optional_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_10_4_optional_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_10_4_optional_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_10_4_optional_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (helicopter_10_4_optional_DW.HILInitialize_Card,
           &helicopter_10_4_optional_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (helicopter_10_4_optional_DW.HILInitialize_Card,
           &helicopter_10_4_optional_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_4_optional_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_10_4_optional_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_10_4_optional_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            helicopter_10_4_optional_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_pwm_channels, 8U,
         (t_pwm_configuration *)
         &helicopter_10_4_optional_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &helicopter_10_4_optional_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &helicopter_10_4_optional_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            helicopter_10_4_optional_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues =
          &helicopter_10_4_optional_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_pwm_channels, 8U,
         &helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[0],
         &helicopter_10_4_optional_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_pwm_outputs_a &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_pwm_outputs_g &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &helicopter_10_4_optional_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter_10_4_optional_DW.HILInitialize_Card,
        helicopter_10_4_optional_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_4_optional_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_4_optional_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues =
          &helicopter_10_4_optional_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_10_4_optional_DW.HILInitialize_Card,
         helicopter_10_4_optional_P.HILInitialize_pwm_channels, 8U,
         &helicopter_10_4_optional_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_10_4_optional/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_10_4_optional_DW.HILInitialize_Card,
       helicopter_10_4_optional_P.HILReadEncoderTimebase_samples_,
       helicopter_10_4_optional_P.HILReadEncoderTimebase_channels, 3,
       &helicopter_10_4_optional_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error creating .mat file travel.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error writing mat file header to file travel.mat");
      return;
    }

    helicopter_10_4_optional_DW.ToFile_IWORK.Count = 0;
    helicopter_10_4_optional_DW.ToFile_IWORK.Decimation = -1;
    helicopter_10_4_optional_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    helicopter_10_4_optional_DW.ToFile1_IWORK.Count = 0;
    helicopter_10_4_optional_DW.ToFile1_IWORK.Decimation = -1;
    helicopter_10_4_optional_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevation.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error creating .mat file elevation.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error writing mat file header to file elevation.mat");
      return;
    }

    helicopter_10_4_optional_DW.ToFile2_IWORK.Count = 0;
    helicopter_10_4_optional_DW.ToFile2_IWORK.Decimation = -1;
    helicopter_10_4_optional_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "traveltrate.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error creating .mat file traveltrate.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"ans")) {
      rtmSetErrorStatus(helicopter_10_4_optional_M,
                        "Error writing mat file header to file traveltrate.mat");
      return;
    }

    helicopter_10_4_optional_DW.ToFile3_IWORK.Count = 0;
    helicopter_10_4_optional_DW.ToFile3_IWORK.Decimation = -1;
    helicopter_10_4_optional_DW.ToFile3_PWORK.FilePtr = fp;
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
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1378421413625261,
      3.1262155534579983, 3.1033093000299643, 3.0666274151911783,
      3.0144539223941584, 2.9456562771175667, 2.8595077632935446,
      2.7555515879651526, 2.633505110490284, 2.4931956060320961,
      2.334518576064299, 2.1585143968629126, 1.9681835024810521,
      1.768089007650641, 1.5635424562165079, 1.3598770542364715,
      1.1619418608751673, 0.97379386151187108, 0.79842889966648478,
      0.63791516513366864, 0.49362142402277925, 0.36627578616995032,
      0.25599137857495552, 0.16235728763115498, 0.084549718195516446,
      0.021442174991925841, -0.028294805128924527, -0.066107935560321171,
      -0.093490258344053834, -0.11192441467862368, -0.12283887983754679,
      -0.12757566122861966, -0.1273678902255867, -0.1233257908564933,
      -0.11642954142073868, -0.10752773341532025, -0.097340206338811644,
      -0.086464168912715925, -0.075382715828746436, -0.064474915484598785,
      -0.054026843017802459, -0.04424301075174978, -0.035257763827347868,
      -0.027146336703517245, -0.019935294726128223, -0.013612248329135875,
      -0.0081347053287851925, -0.0034380281411618033, 0.00055750090758689371,
      0.00394050159918529, 0.0068031520743573421, 0.0092366421395133468,
      0.011327376786050272, 0.013153903595217785, 0.01478460096502658,
      0.016276165739117273, 0.017673016557236371, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909068425, -0.046506351618112118,
      -0.091625013712135411, -0.14672753935514374, -0.20869397118807928,
      -0.27519058110636674, -0.34459405529608839, -0.41582470131356869,
      -0.48818590989947463, -0.56123801783275185, -0.63470811987118858,
      -0.70401671680554512, -0.76132357752744262, -0.800377979321644,
      -0.81818620573653233, -0.814661607920146, -0.79174077344521743,
      -0.75259199745318439, -0.70145984738154554, -0.64205493813126446,
      -0.57717496444355743, -0.50938255141131561, -0.44113763037997933,
      -0.37453636377520216, -0.31123027774255418, -0.25243017281436242,
      -0.19894792048340149, -0.15125252172558659, -0.10952929113493071,
      -0.073736625338279363, -0.04365786063569245, -0.018947125564291425,
      0.0008310840121318005, 0.016168397476373549, 0.02758499774301848,
      0.035607232021673742, 0.04075010830603442, 0.043504149704382863,
      0.044325812335877991, 0.043631201376590628, 0.041792289867185285,
      0.0391353290642107, 0.035940987697607639, 0.032445708495322488,
      0.028844167909556087, 0.025292185587969383, 0.021910172001402731,
      0.018786708750493555, 0.015982116194994789, 0.013532002766393585,
      0.011450601900688208, 0.0097339602606240153, 0.0083629385861477019,
      0.0073061072366700482, 0.006522789479235183, 0.0059662590963627735,
      0.0055874032724763933, 0.0053390183437922959, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.10602875205865553, 0.22266037932317662,
      0.31888147181640647, 0.3894436063114417, 0.43795507377677845,
      0.46997264230390068, 0.49051724877547076, 0.5034310014147434,
      0.5114213858602934, 0.51630439857701838, 0.51925862127063693,
      0.48984669257037577, 0.40502300476230652, 0.27602159609901089,
      0.12586174292547642, -0.024910511240515125, -0.16199570407017155,
      -0.27668859688558839, -0.36138250815157585, -0.41985121046749851,
      -0.4585468748570522, -0.47913088381604829, -0.4823290375303414,
      -0.47071231579319239, -0.44742323801531697, -0.41557668450777729,
      -0.37799213336187132, -0.33709286244055381, -0.29488385874469664,
      -0.25296889180100168, -0.21258522113958805, -0.17464603788146155,
      -0.1397848315289171, -0.10839827388930628, -0.080688170420052524,
      -0.056698088004087453, -0.03634788539405439, -0.019464512771202057,
      -0.0058071976673797956, 0.0049092449721974563, 0.012996724225494761,
      0.018778384200431979, 0.022576384786049512, 0.024703298473507045,
      0.025454313348264063, 0.025104054464493191, 0.023902780360375957,
      0.022075445334322395, 0.019821789043280472, 0.017316465958173641,
      0.014710546383510652, 0.012132567486692213, 0.0096898575702029539,
      0.0074692803496891613, 0.005536190742319127, 0.003933344194273233,
      0.0026776082693974485, 0.0017554898119705128, 0.0011209458126823042, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462212,
      0.46652650905808429, 0.38488436997291953, 0.282248537980141,
      0.19404586986134692, 0.12807027410848895, 0.082178425886280368,
      0.051655010557090479, 0.03196153778219981, 0.01953205086689986,
      0.011816890774474375, -0.11764771480104445, -0.33929475123227726,
      -0.51600563465318239, -0.6006394126941379, -0.60308901666396619,
      -0.5483407713186258, -0.45877157126166745, -0.33877564506394986,
      -0.23387480926369045, -0.15478265755821463, -0.0823360358359843,
      -0.012792614857172563, 0.046466886948595909, 0.093156311111501813,
      0.12738621403015873, 0.15033820458362374, 0.16359708368527012,
      0.16883601478342875, 0.16765986777477992, 0.16153468264565443,
      0.15175673303250609, 0.13944482541017778, 0.12554623055844324,
      0.11084041387701503, 0.095960329663860269, 0.081400810440132254,
      0.067533490491409345, 0.054629260415289045, 0.042865770558309008,
      0.032349917013189219, 0.023126639899748856, 0.015192002342470135,
      0.0085076547498301267, 0.0030040594990280735, -0.0014010355350834861,
      -0.004805096416468941, -0.0073093401042142519, -0.00901462516416768,
      -0.010021292340427344, -0.010423678298651947, -0.010311915587273757,
      -0.00977083966595704, -0.0088823088820551722, -0.0077323584294801354,
      -0.0064113861921835788, -0.0050229436995031379, -0.0036884738297077425,
      -0.0025381759971528348, -0.0016753493597539376, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0044617507837353427, 0.012542979268776903,
      0.023529262006077065, 0.036805941713369004, 0.051832632941115939,
      0.0681197271226632, 0.085206098320620358, 0.10263742077254361,
      0.11994456311217297, 0.13662118888622093, 0.15210024169116992,
      0.16572828663352415, 0.17673727833040054, 0.18421281418256508,
      0.18705795954971383, 0.1863134867373144, 0.18283234471761767,
      0.17731033105202884, 0.17031205288967768, 0.16229285489405404,
      0.1536173096220014, 0.14457482341263123, 0.13539269332623249,
      0.12624710763173039, 0.11727239210644083, 0.10856874365964413,
      0.10020861583613244, 0.092242120718356857, 0.084701478633949154,
      0.0776047166338574, 0.070958686322500422, 0.0647615810312139,
      0.059005020721396247, 0.053675700756832659, 0.048756760129280534,
      0.044228883987357234, 0.040071175750446074, 0.036261834755225646,
      0.032778747120863136, 0.029599863878746326, 0.026703563082385473,
      0.024068858746970647, 0.021675609506944457, 0.019504610414383096,
      0.017537693572973925, 0.015757760352224412, 0.014148796916556584,
      0.012695873649166732, 0.011385121994340539, 0.010203702148763068,
      0.0091397492400725217, 0.00818235241909196, 0.0073215171465360563,
      0.0065480453029450611, 0.0058535582661917275, 0.0052303919494813573,
      0.0046715484891325038, 0.0041707015905087085, 0.0037220862780819406, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.017847003134941371,
      0.03232491394016624, 0.043945130949200661, 0.053106718829167752,
      0.06010676491098773, 0.065148376726189, 0.068345484791828642,
      0.069725289807692978, 0.069228569358517469, 0.06670650309619186,
      0.06191621121979593, 0.054512179769416892, 0.044035966787505633,
      0.029902143408658152, 0.011380581468594988, -0.0029778912495976562,
      -0.013924568078786993, -0.022088054662355347, -0.027993112649404676,
      -0.032076791982494593, -0.034702181088210521, -0.036169944837480671,
      -0.036728520345595032, -0.036582342778008425, -0.03589886210115821,
      -0.034814593787186827, -0.03344051129404671, -0.031865980471102347,
      -0.0301625683376308, -0.028387048000367052, -0.026584121245427861,
      -0.024788421165146065, -0.023026241239270641, -0.021317279858254361,
      -0.019675762510208507, -0.018111504567693195, -0.016630832947644669,
      -0.0152373639808817, -0.013932350537450022, -0.012715532968467251,
      -0.011585203185443415, -0.010538817341659314, -0.0095729969601047633,
      -0.0086839963702454344, -0.0078676673656366963, -0.0071197328829980481,
      -0.0064358537426713117, -0.0058116930695594074, -0.005243006619304779,
      -0.004725679382309886, -0.0042558116347621838, -0.0038295872839222509,
      -0.0034433410902236124, -0.0030938873743639808, -0.0027779481470133305,
      -0.002492665266841481, -0.0022353738413954161, -0.0020033875944951815,
      -0.0017944612497070706, -0.0016065147866870971, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_4_optional_DW.FromWorkspace1_PWORK.TimePtr = (void *)
      pTimeValues0;
    helicopter_10_4_optional_DW.FromWorkspace1_PWORK.DataPtr = (void *)
      pDataValues0;
    helicopter_10_4_optional_DW.FromWorkspace1_IWORK.PrevIndex = 0;
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
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.36960143082579383, 0.11490062157659643, -0.10530905993574098,
      -0.27280273502635954, -0.39437973154858458, -0.47664673812665814,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.50239166735658836, -0.46417528383677331,
      -0.42018502155146414, -0.3730578987443634, -0.32494616404133003,
      -0.27754720939728261, -0.23216524842517516, -0.18974977976322727,
      -0.15094932380297721, -0.11615707372225662, -0.0855574538158898,
      -0.059166514834739704, -0.0368661020574795, -0.018444349033644666,
      -0.003612732807628821, 0.0079597030043255142, 0.016627108844549713,
      0.022758178020943261, 0.026711838484082012, 0.028838901045408247,
      0.029466835340629473, 0.028897141944624692, 0.027406105824608663,
      0.025234772470055761, 0.02260275343031409, 0.019695062900164574,
      0.016673399572434727, 0.013676001158220086, 0.010816396168877241,
      0.0081902469882073718, 0.0058725798379161559, 0.0039208573622394648,
      0.0023730305540262055, 0.0012403173957898457, 0.00050860090618846433,
      0.00012655484073298038, -2.1069431618408943E-7, -5.7520490139170182E-7,
      5.1233044131053683E-7, 5.1233044131053683E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.285552050159062, 0.30303458542336348, 0.319684878688951,
      0.33490890914505311, 0.34795687463186775, 0.3578987904005404,
      0.36357986889610627, 0.36357854654380722, 0.3561597303645842,
      0.33919863800940392, 0.3101259054746055, 0.2658215305593401,
      0.20252955305825734, 0.11573097972198693, 8.6092402249426976E-7,
      -4.2343413731394E-7, -4.347157062171414E-7, -5.709149272416414E-7,
      -8.0172459298549175E-7, -9.8887502859252328E-7, -1.3407317556207104E-6,
      -8.9447110490601214E-8, 3.2214224887447406E-7, -4.1688836315961914E-7,
      -9.8695619780367657E-7, -4.7749360471132532E-8, -6.6315206457917183E-7,
      -8.0834943298073849E-7, -7.1191273214134008E-7, 1.7276405356852471E-7,
      1.1471150803679486E-7, -5.6706334535515028E-7, -1.1952407704274326E-7,
      -1.8296081510759143E-9, 1.7885711251088809E-7, 7.7779624356487507E-7,
      1.4877792841618466E-6, 1.0556649860446651E-6, 1.9349218261152313E-6,
      1.5137091498826774E-6, 1.8917753754885677E-6, 1.2246375182582528E-6,
      1.4198206210295611E-6, 8.8034430085671627E-7, 8.8809970253622479E-7,
      8.9267405467629488E-7, 8.2828620950608993E-7, 9.1615132962801369E-7,
      1.0078423930067338E-6, 1.0829638659038084E-6, 2.8842586422461734E-7,
      4.5223153257064792E-8, 1.3392035617361969E-6, 2.4751195161642739E-7,
      9.9528669053965551E-7, 7.7879764133279827E-7, -4.3999403716119E-7,
      6.76534303442885E-7, 8.196277615575395E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_4_optional_DW.FromWorkspace2_PWORK.TimePtr = (void *)
      pTimeValues0;
    helicopter_10_4_optional_DW.FromWorkspace2_PWORK.DataPtr = (void *)
      pDataValues0;
    helicopter_10_4_optional_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_10_4_optional_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_10_4_optional_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_10_4_optional_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_10_4_optional_X.Integrator_CSTATE =
    helicopter_10_4_optional_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_10_4_optional_DW.TimeStampA = (rtInf);
  helicopter_10_4_optional_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_10_4_optional_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_4_optional/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_10_4_optional_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_10_4_optional_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_10_4_optional_P.HILInitialize_set_analog_out_ex &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_analog_outp_c &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            helicopter_10_4_optional_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter_10_4_optional_P.HILInitialize_set_pwm_output_ap &&
         !is_switching) ||
        (helicopter_10_4_optional_P.HILInitialize_set_pwm_outputs_p &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &helicopter_10_4_optional_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            helicopter_10_4_optional_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_10_4_optional_DW.HILInitialize_Card
                         ,
                         helicopter_10_4_optional_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter_10_4_optional_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         ,
                         &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_10_4_optional_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (helicopter_10_4_optional_DW.HILInitialize_Card,
             helicopter_10_4_optional_P.HILInitialize_analog_output_cha,
             num_final_analog_outputs,
             &helicopter_10_4_optional_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (helicopter_10_4_optional_DW.HILInitialize_Card,
             helicopter_10_4_optional_P.HILInitialize_pwm_channels,
             num_final_pwm_outputs,
             &helicopter_10_4_optional_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_optional_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_10_4_optional_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_10_4_optional_DW.HILInitialize_Card);
    hil_close(helicopter_10_4_optional_DW.HILInitialize_Card);
    helicopter_10_4_optional_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file travel.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error reopening MAT-file travel.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2,
           helicopter_10_4_optional_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error writing header for ans to MAT-file travel.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file travel.mat");
        return;
      }

      helicopter_10_4_optional_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2,
           helicopter_10_4_optional_DW.ToFile1_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error writing header for ans to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file pitch.mat");
        return;
      }

      helicopter_10_4_optional_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevation.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file elevation.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error reopening MAT-file elevation.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2,
           helicopter_10_4_optional_DW.ToFile2_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error writing header for ans to MAT-file elevation.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file elevation.mat");
        return;
      }

      helicopter_10_4_optional_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (FILE *) helicopter_10_4_optional_DW.ToFile3_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "traveltrate.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file traveltrate.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error reopening MAT-file traveltrate.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2,
           helicopter_10_4_optional_DW.ToFile3_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error writing header for ans to MAT-file traveltrate.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_optional_M,
                          "Error closing MAT-file traveltrate.mat");
        return;
      }

      helicopter_10_4_optional_DW.ToFile3_PWORK.FilePtr = (NULL);
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
  helicopter_10_4_optional_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_10_4_optional_update();
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
  helicopter_10_4_optional_initialize();
}

void MdlTerminate(void)
{
  helicopter_10_4_optional_terminate();
}

/* Registration function */
RT_MODEL_helicopter_10_4_opti_T *helicopter_10_4_optional(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_10_4_optional_P.Integrator_UpperSat = rtInf;
  helicopter_10_4_optional_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_10_4_optional_M, 0,
                sizeof(RT_MODEL_helicopter_10_4_opti_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_10_4_optional_M->solverInfo,
                          &helicopter_10_4_optional_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_10_4_optional_M->solverInfo, &rtmGetTPtr
                (helicopter_10_4_optional_M));
    rtsiSetStepSizePtr(&helicopter_10_4_optional_M->solverInfo,
                       &helicopter_10_4_optional_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_10_4_optional_M->solverInfo,
                 &helicopter_10_4_optional_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter_10_4_optional_M->solverInfo, (real_T **)
                         &helicopter_10_4_optional_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter_10_4_optional_M->solverInfo,
      &helicopter_10_4_optional_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_10_4_optional_M->solverInfo,
      &helicopter_10_4_optional_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_10_4_optional_M->solverInfo,
      &helicopter_10_4_optional_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_10_4_optional_M->solverInfo,
      &helicopter_10_4_optional_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_10_4_optional_M->solverInfo,
                          (&rtmGetErrorStatus(helicopter_10_4_optional_M)));
    rtsiSetRTModelPtr(&helicopter_10_4_optional_M->solverInfo,
                      helicopter_10_4_optional_M);
  }

  rtsiSetSimTimeStep(&helicopter_10_4_optional_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_10_4_optional_M->ModelData.intgData.f[0] =
    helicopter_10_4_optional_M->ModelData.odeF[0];
  helicopter_10_4_optional_M->ModelData.contStates = ((real_T *)
    &helicopter_10_4_optional_X);
  rtsiSetSolverData(&helicopter_10_4_optional_M->solverInfo, (void *)
                    &helicopter_10_4_optional_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter_10_4_optional_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_10_4_optional_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_10_4_optional_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_10_4_optional_M->Timing.sampleTimes =
      (&helicopter_10_4_optional_M->Timing.sampleTimesArray[0]);
    helicopter_10_4_optional_M->Timing.offsetTimes =
      (&helicopter_10_4_optional_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_10_4_optional_M->Timing.sampleTimes[0] = (0.0);
    helicopter_10_4_optional_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_10_4_optional_M->Timing.offsetTimes[0] = (0.0);
    helicopter_10_4_optional_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_10_4_optional_M,
             &helicopter_10_4_optional_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_10_4_optional_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_10_4_optional_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_10_4_optional_M, -1);
  helicopter_10_4_optional_M->Timing.stepSize0 = 0.002;
  helicopter_10_4_optional_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_10_4_optional_M->Sizes.checksums[0] = (1094680152U);
  helicopter_10_4_optional_M->Sizes.checksums[1] = (1760930674U);
  helicopter_10_4_optional_M->Sizes.checksums[2] = (3094032520U);
  helicopter_10_4_optional_M->Sizes.checksums[3] = (1506356078U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter_10_4_optional_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter_10_4_optional_M->extModeInfo,
      &helicopter_10_4_optional_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_10_4_optional_M->extModeInfo,
                        helicopter_10_4_optional_M->Sizes.checksums);
    rteiSetTPtr(helicopter_10_4_optional_M->extModeInfo, rtmGetTPtr
                (helicopter_10_4_optional_M));
  }

  helicopter_10_4_optional_M->solverInfoPtr =
    (&helicopter_10_4_optional_M->solverInfo);
  helicopter_10_4_optional_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_10_4_optional_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_10_4_optional_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_10_4_optional_M->ModelData.blockIO = ((void *)
    &helicopter_10_4_optional_B);

  {
    helicopter_10_4_optional_B.TravelCounttorad = 0.0;
    helicopter_10_4_optional_B.Gain = 0.0;
    helicopter_10_4_optional_B.Sum5 = 0.0;
    helicopter_10_4_optional_B.PitchCounttorad = 0.0;
    helicopter_10_4_optional_B.Gain_i = 0.0;
    helicopter_10_4_optional_B.ElevationCounttorad = 0.0;
    helicopter_10_4_optional_B.Gain_e = 0.0;
    helicopter_10_4_optional_B.Sum = 0.0;
    helicopter_10_4_optional_B.Gain_d = 0.0;
    helicopter_10_4_optional_B.Gain_b = 0.0;
    helicopter_10_4_optional_B.Gain_dg = 0.0;
    helicopter_10_4_optional_B.Sum1 = 0.0;
    helicopter_10_4_optional_B.Sum2 = 0.0;
    helicopter_10_4_optional_B.K_ei = 0.0;
    helicopter_10_4_optional_B.Gain_l = 0.0;
    helicopter_10_4_optional_B.BackmotorSaturation = 0.0;
    helicopter_10_4_optional_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter_10_4_optional_M->ModelData.defaultParam = ((real_T *)
    &helicopter_10_4_optional_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_10_4_optional_X;
    helicopter_10_4_optional_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter_10_4_optional_X, 0,
                  sizeof(X_helicopter_10_4_optional_T));
  }

  /* states (dwork) */
  helicopter_10_4_optional_M->ModelData.dwork = ((void *)
    &helicopter_10_4_optional_DW);
  (void) memset((void *)&helicopter_10_4_optional_DW, 0,
                sizeof(DW_helicopter_10_4_optional_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_optional_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_10_4_optional_DW.TimeStampA = 0.0;
  helicopter_10_4_optional_DW.LastUAtTimeA = 0.0;
  helicopter_10_4_optional_DW.TimeStampB = 0.0;
  helicopter_10_4_optional_DW.LastUAtTimeB = 0.0;
  helicopter_10_4_optional_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_10_4_optional_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_10_4_optional_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_10_4_optional_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_10_4_optional_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter_10_4_optional_M->Sizes.numY = (0);/* Number of model outputs */
  helicopter_10_4_optional_M->Sizes.numU = (0);/* Number of model inputs */
  helicopter_10_4_optional_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_10_4_optional_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_10_4_optional_M->Sizes.numBlocks = (62);/* Number of blocks */
  helicopter_10_4_optional_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  helicopter_10_4_optional_M->Sizes.numBlockPrms = (153);/* Sum of parameter "widths" */
  return helicopter_10_4_optional_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
