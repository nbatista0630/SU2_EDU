/*!
 * \file variable_structure.hpp
 * \brief Headers of the main subroutines for storing all the variables for 
 *        each kind of governing equation (direct, adjoint and linearized).
 *        The subroutines and functions are in the <i>variable_structure.cpp</i> file.
 * \author Aerospace Design Laboratory (Stanford University).
 * \version 1.2.0
 *
 * SU2 EDU, Copyright (C) 2014 Aerospace Design Laboratory (Stanford University).
 *
 * SU2 EDU is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 EDU is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2 EDU. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "config_structure.hpp"

using namespace std;

/*! 
 * \class CVariable
 * \brief Main class for defining the variables.
 * \author F. Palacios.
 * \version 1.2.0
 */
class CVariable {
protected:

	double *Solution,		/*!< \brief Solution of the problem. */
	*Solution_Old;			/*!< \brief Old solution of the problem R-K. */
	double *Solution_time_n,	/*!< \brief Solution of the problem at time n for dual-time stepping technique. */
	*Solution_time_n1;			/*!< \brief Solution of the problem at time n-1 for dual-time stepping technique. */
	double **Gradient;		/*!< \brief Gradient of the solution of the problem. */ 
	double *Limiter;				/*!< \brief Limiter of the solution of the problem. */
	double *Solution_Max;		/*!< \brief Max solution for limiter computation. */
	double *Solution_Min;		/*!< \brief Min solution for limiter computation. */
	double AuxVar;			/*!< \brief Auxiliar variable for gradient computation. */
	double *Grad_AuxVar;	/*!< \brief Gradient of the auxiliar variable. */
	double Delta_Time;	/*!< \brief Time step. */
	double Max_Lambda,	/*!< \brief Maximun eingenvalue. */
	Max_Lambda_Inv,		/*!< \brief Maximun inviscid eingenvalue. */
	Max_Lambda_Visc,	/*!< \brief Maximun viscous eingenvalue. */
	Lambda;				/*!< \brief Value of the eingenvalue. */
	double Sensor;	/*!< \brief Pressure sensor for high order central scheme. */
	double *Undivided_Laplacian;	/*!< \brief Undivided laplacian of the solution. */
	double *Res_TruncError,	/*!< \brief Truncation error for multigrid cycle. */
	*Residual_Old,		/*!< \brief Auxiliar structure for residual smoothing. */
	*Residual_Sum;		/*!< \brief Auxiliar structure for residual smoothing. */
	static unsigned short nDim;		/*!< \brief Number of dimension of the problem. */
	unsigned short nVar;		/*!< \brief Number of variables of the problem, 
													 note that this variable cannnot be static, it is possible to 
													 have different number of nVar in the same problem. */
  unsigned short nPrimVar, nPrimVarGrad;		/*!< \brief Number of variables of the problem,
                                             note that this variable cannnot be static, it is possible to
                                             have different number of nVar in the same problem. */
  
public:

	/*!
	 * \brief Constructor of the class. 
	 */
	CVariable(void);

  /*!
	 * \overload
	 * \param[in] val_nVar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CVariable(unsigned short val_nVar, CConfig *config);
  
	/*!
	 * \overload 
	 * \param[in] val_nDim - Number of dimensions of the problem.		 
	 * \param[in] val_nVar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.	 
	 */
	CVariable(unsigned short val_nDim, unsigned short val_nVar, CConfig *config);

	/*!
	 * \brief Destructor of the class. 
	 */
	virtual ~CVariable(void);

	/*!
	 * \brief Set the value of the solution.
	 * \param[in] val_solution - Solution of the problem.
	 */
	void SetSolution(double *val_solution);

	/*!
	 * \overload
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_solution - Value of the solution for the index <i>val_var</i>.
	 */
	void SetSolution(unsigned short val_var, double val_solution);

	/*!
	 * \brief Get the solution.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the solution for the index <i>val_var</i>.
	 */
	double GetSolution(unsigned short val_var);

	/*!
	 * \brief Get the old solution of the problem (Runge-Kutta method)
	 * \param[in] val_var - Index of the variable.
	 * \return Pointer to the old solution vector.
	 */
	double GetSolution_Old(unsigned short val_var);

	/*!
	 * \brief Set the value of the old solution.
	 * \param[in] val_solution_old - Pointer to the residual vector.
	 */
	void SetSolution_Old(double *val_solution_old);

	/*!
	 * \overload
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_solution_old - Value of the old solution for the index <i>val_var</i>.
	 */	
	void SetSolution_Old(unsigned short val_var, double val_solution_old);

	/*!
	 * \brief Set old variables to the value of the current variables.
	 */
	void Set_OldSolution(void);

	/*!
	 * \brief Set variables to the value of the old variables.
	 */
	void Set_Solution(void);	

	/*!
	 * \brief Set the variable solution at time n.
	 */	
	void Set_Solution_time_n(void);

	/*!
	 * \brief Set the variable solution at time n-1.
	 */	
	void Set_Solution_time_n1(void);

	/*!
	 * \brief Set to zero the velocity components of the solution.
	 */
	void SetVelSolutionZero(void);

  /*!
	 * \brief Specify a vector to set the velocity components of the solution.
   * \param[in] val_vector - Pointer to the vector.
	 */
	void SetVelSolutionVector(double *val_vector);
  
	/*!
	 * \brief Set to zero velocity components of the solution.
	 */
	void SetVelSolutionOldZero(void);

  /*!
	 * \brief Specify a vector to set the velocity components of the old solution.
   * \param[in] val_vector - Pointer to the vector.
	 */
	void SetVelSolutionOldVector(double *val_vector);
  
	/*!
	 * \brief Set to zero the solution.
	 */	
	void SetSolutionZero(void);
  
  /*!
	 * \brief Set to zero a particular solution.
	 */
  void SetSolutionZero(unsigned short val_var);

	/*!
	 * \brief Add a value to the solution.
	 * \param[in] val_var - Number of the variable.
	 * \param[in] val_solution - Value that we want to add to the solution.
	 */
	void AddSolution(unsigned short val_var, double val_solution);

  /*!
	 * \brief Add a value to the solution, clipping the values.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_solution - Value of the solution change.
   * \param[in] lowerlimit - Lower value.
   * \param[in] upperlimit - Upper value.
	 */
	void AddClippedSolution(unsigned short val_var, double val_solution,
                          double lowerlimit, double upperlimit);
  
	/*!
	 * \brief Update the variables using a conservative format.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_solution - Value of the solution change.
	 * \param[in] val_density - Value of the density.
	 * \param[in] val_density_old - Value of the old density.
	 */
	void AddConservativeSolution(unsigned short val_var, double val_solution,
			double val_density, double val_density_old, double lowerlimit,
			double upperlimit);

	/*!
	 * \brief Get the solution of the problem.
	 * \return Pointer to the solution vector.
	 */
	double *GetSolution(void);

	/*!
	 * \brief Get the old solution of the problem (Runge-Kutta method)
	 * \return Pointer to the old solution vector.
	 */
	double *GetSolution_Old(void);

	/*!
	 * \brief Get the solution at time n.
	 * \return Pointer to the solution (at time n) vector.
	 */	
	double *GetSolution_time_n(void);

	/*!
	 * \brief Get the solution at time n-1.
	 * \return Pointer to the solution (at time n-1) vector.
	 */	
	double *GetSolution_time_n1(void);

	/*!
	 * \brief Set the value of the old residual.
	 * \param[in] val_residual_old - Pointer to the residual vector.
	 */
	void SetResidual_Old(double *val_residual_old);

	/*!
	 * \brief Add a value to the summed residual vector.
	 * \param[in] val_residual - Pointer to the residual vector.
	 */
	void AddResidual_Sum(double *val_residual);

	/*!
	 * \brief Set summed residual vector to zero value.
	 */
	void SetResidualSumZero(void);
  
  /*!
	 * \brief Set the velocity of the truncation error to zero.
	 */
	virtual void SetVel_ResTruncError_Zero(unsigned short iSpecies);

	/*!
	 * \brief Get the value of the summed residual.
	 * \return Pointer to the summed residual.
	 */	
	double *GetResidual_Sum(void);

	/*!
	 * \brief Get the value of the old residual.
	 * \return Pointer to the old residual.
	 */	
	double *GetResidual_Old(void);

	/*!
	 * \brief Get the value of the summed residual.
	 * \param[out] val_residual - Pointer to the summed residual.
	 */	
	void GetResidual_Sum(double *val_residual);

	/*!
	 * \brief Set auxiliar variables, we are looking for the gradient of that variable.
	 * \param[in] val_auxvar - Value of the auxiliar variable.
	 */
	void SetAuxVar(double val_auxvar);

	/*!
	 * \brief Get the value of the auxiliary variable.
	 * \return Value of the auxiliary variable.
	 */
	double GetAuxVar(void);

	/*!
	 * \brief Set the auxiliary variable gradient to zero value.
	 */
	void SetAuxVarGradientZero(void);

	/*!
	 * \brief Set the value of the auxiliary variable gradient.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_gradient - Value of the gradient for the index <i>val_dim</i>.
	 */
	void SetAuxVarGradient(unsigned short val_dim, double val_gradient);

	/*!
	 * \brief Add a value to the auxiliary variable gradient.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient to be added for the index <i>val_dim</i>.
	 */		
	void AddAuxVarGradient(unsigned short val_dim, double val_value);

	/*!
	 * \brief Subtract a value to the auxiliary variable gradient.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient to be subtracted for the index <i>val_dim</i>.
	 */		
	void SubtractAuxVarGradient(unsigned short val_dim, double val_value);

	/*!
	 * \brief Get the gradient of the auxiliary variable.
	 * \return Value of the gradient of the auxiliary variable.
	 */		
	double *GetAuxVarGradient(void);

	/*!
	 * \brief Get the gradient of the auxiliary variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the gradient of the auxiliary variable for the dimension <i>val_dim</i>.
	 */		
	double GetAuxVarGradient(unsigned short val_dim);	

	/*!
	 * \brief Add a value to the truncation error.
	 * \param[in] val_truncation_error - Value that we want to add to the truncation error.
	 */		
	void AddRes_TruncError(double *val_truncation_error);

	/*!
	 * \brief Subtract a value to the truncation error.
	 * \param[in] val_truncation_error - Value that we want to subtract to the truncation error.
	 */		
	void SubtractRes_TruncError(double *val_truncation_error);

	/*!
	 * \brief Set the truncation error to zero.
	 */		
	void SetRes_TruncErrorZero(void);
  
  /*!
	 * \brief Set the truncation error to zero.
	 */
	void SetVal_ResTruncError_Zero(unsigned short val_var);

	/*!
	 * \brief Set the velocity of the truncation error to zero.
	 */		
	void SetVel_ResTruncError_Zero(void);
  
  /*!
	 * \brief Set the velocity of the truncation error to zero.
	 */
	void SetEnergy_ResTruncError_Zero(void);

	/*!
	 * \brief Get the truncation error.
	 * \return Pointer to the truncation error.
	 */	
	double *GetResTruncError(void);

	/*!
	 * \brief Get the truncation error.
	 * \param[out] val_trunc_error - Pointer to the truncation error.
	 */	
	void GetResTruncError(double *val_trunc_error);

	/*!
	 * \brief Set the gradient of the solution.
	 * \param[in] val_gradient - Gradient of the solution.
	 */
	void SetGradient(double **val_gradient);

	/*!
	 * \overload
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient.
	 */
	void SetGradient(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief Set to zero the gradient of the solution.
	 */
	void SetGradientZero(void);

	/*!
	 * \brief Add <i>val_value</i> to the solution gradient.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value to add to the solution gradient.
	 */
	void AddGradient(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief Subtract <i>val_value</i> to the solution gradient.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value to subtract to the solution gradient.
	 */
	void SubtractGradient(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief Get the value of the solution gradient.
	 * \return Value of the gradient solution.
	 */
	double **GetGradient(void);

	/*!
	 * \brief Get the value of the solution gradient.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the solution gradient.
	 */
	double GetGradient(unsigned short val_var, unsigned short val_dim);

	/*!
	 * \brief Set the value of the limiter.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_limiter - Value of the limiter for the index <i>val_var</i>.
	 */
	void SetLimiter(unsigned short val_var, double val_limiter);
  
  /*!
	 * \brief Set the value of the limiter.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_limiter - Value of the limiter for the index <i>val_var</i>.
	 */
	virtual void SetLimiterPrimitive(unsigned short val_species, unsigned short val_var, double val_limiter);
  
  /*!
	 * \brief Set the value of the limiter.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_limiter - Value of the limiter for the index <i>val_var</i>.
	 */
  virtual double GetLimiterPrimitive(unsigned short val_species, unsigned short val_var);
	
	/*!
	 * \brief Set the value of the max solution.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_limiter - Value of the max solution for the index <i>val_var</i>.
	 */
	void SetSolution_Max(unsigned short val_var, double val_solution);
	
	/*!
	 * \brief Set the value of the min solution.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_limiter - Value of the min solution for the index <i>val_var</i>.
	 */
	void SetSolution_Min(unsigned short val_var, double val_solution);

	/*!
	 * \brief Get the value of the slope limiter.
	 * \return Pointer to the limiters vector.
	 */
	double *GetLimiter(void);

	/*!
	 * \brief Get the value of the slope limiter.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the limiter vector for the variable <i>val_var</i>.
	 */
	double GetLimiter(unsigned short val_var);
	
	/*!
	 * \brief Get the value of the min solution.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the min solution for the variable <i>val_var</i>.
	 */
	double GetSolution_Max(unsigned short val_var);
	
	/*!
	 * \brief Get the value of the min solution.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the min solution for the variable <i>val_var</i>.
	 */
	double GetSolution_Min(unsigned short val_var);

	/*!
	 * \brief Get the value of the preconditioner Beta.
	 * \return Value of the low Mach preconditioner variable Beta
	 */
	virtual double GetPreconditioner_Beta();

	/*!
	 * \brief Set the value of the preconditioner Beta.
	 * \param[in] Value of the low Mach preconditioner variable Beta
	 */
	virtual void SetPreconditioner_Beta(double val_Beta);
    
	/*!
	 * \brief Set the value of the time step.
	 * \param[in] val_delta_time - Value of the time step.
	 */
	void SetDelta_Time(double val_delta_time);

	/*!
	 * \brief Set the value of the time step.
	 * \param[in] val_delta_time - Value of the time step.
	 * \param[in] iSpecies - Index of the Species .
	 */
	virtual void SetDelta_Time(double val_delta_time, unsigned short iSpecies);

	/*!
	 * \brief Get the value of the time step.
	 * \return Value of the time step.
	 */
	double GetDelta_Time(void);

	/*!
	 * \brief Get the value of the time step.
	 * \param[in] iSpecies - Index of the Species
	 * \return Value of the time step.
	 */
	virtual double GetDelta_Time(unsigned short iSpecies);

	/*!
	 * \brief Set the value of the maximum eigenvalue.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue.
	 */
	void SetMax_Lambda(double val_max_lambda);

	/*!
	 * \brief Set the value of the maximum eigenvalue for the inviscid terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the inviscid terms of the PDE.
	 */
	void SetMax_Lambda_Inv(double val_max_lambda);

	/*!
	 * \brief Set the value of the maximum eigenvalue for the inviscid terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the inviscid terms of the PDE.
	 * \param[in] val_species - Value of the species index to set the maximum eigenvalue.
	 */
	virtual void SetMax_Lambda_Inv(double val_max_lambda, unsigned short val_species);

	/*!
	 * \brief Set the value of the maximum eigenvalue for the viscous terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the viscous terms of the PDE.
	 */
	void SetMax_Lambda_Visc(double val_max_lambda);

	/*!
	 * \brief Set the value of the maximum eigenvalue for the viscous terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the viscous terms of the PDE.
	 * \param[in] val_species - Index of the species to set the maximum eigenvalue of the viscous terms.
	 */
	virtual void SetMax_Lambda_Visc(double val_max_lambda, unsigned short val_species);

	/*!
	 * \brief Add a value to the maximum eigenvalue.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue.
	 */
	void AddMax_Lambda(double val_max_lambda);

	/*!
	 * \brief Add a value to the maximum eigenvalue for the inviscid terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the inviscid terms of the PDE.
	 */
	void AddMax_Lambda_Inv(double val_max_lambda);

	/*!
	 * \brief Add a value to the maximum eigenvalue for the viscous terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the viscous terms of the PDE.
	 */
	void AddMax_Lambda_Visc(double val_max_lambda);

	/*!
	 * \brief Get the value of the maximum eigenvalue.
	 * \return the value of the maximum eigenvalue.
	 */
	double GetMax_Lambda(void);

	/*!
	 * \brief Get the value of the maximum eigenvalue for the inviscid terms of the PDE.
	 * \return the value of the maximum eigenvalue for the inviscid terms of the PDE.
	 */	
	double GetMax_Lambda_Inv(void);

	/*!
	 * \brief Get the value of the maximum eigenvalue for the viscous terms of the PDE.
	 * \return the value of the maximum eigenvalue for the viscous terms of the PDE.
	 */
	double GetMax_Lambda_Visc(void);

	/*!
	 * \brief Set the value of the spectral radius.
	 * \param[in] val_lambda - Value of the spectral radius.
	 */
	void SetLambda(double val_lambda);

	/*!
	 * \brief Set the value of the spectral radius.
	 * \param[in] val_lambda - Value of the spectral radius.
	 * \param[in] val_iSpecies -Index of species
	 */
	virtual void SetLambda(double val_lambda, unsigned short val_iSpecies);

	/*!
	 * \brief Add the value of the spectral radius.
	 * \param[in] val_lambda - Value of the spectral radius.
	 */
	void AddLambda(double val_lambda);

	/*!
	 * \brief Add the value of the spectral radius.
	 * \param[in] val_iSpecies -Index of species
	 * \param[in] val_lambda - Value of the spectral radius.
	 */
	virtual void AddLambda(double val_lambda, unsigned short val_iSpecies);

	/*!
	 * \brief Get the value of the spectral radius.
	 * \return Value of the spectral radius.
	 */
	double GetLambda(void);

	/*!
	 * \brief Get the value of the spectral radius.
	 * \param[in] val_iSpecies -Index of species
	 * \return Value of the spectral radius.
	 */
	virtual double GetLambda(unsigned short val_iSpecies);

	/*!
	 * \brief Set pressure sensor.
	 * \param[in] val_sensor - Value of the pressure sensor.
	 */
	void SetSensor(double val_sensor);

	/*!
	 * \brief Set pressure sensor.
	 * \param[in] val_sensor - Value of the pressure sensor.
	 * \param[in] val_sensor - Index of the Species.
	 */
	virtual void SetSensor(double val_sensor, unsigned short iSpecies);

	/*!
	 * \brief Get the pressure sensor.
	 * \return Value of the pressure sensor.
	 */	
	double GetSensor(void);

	/*!
	 * \brief Get the pressure sensor.
	 * \param[in] iSpecies - index of species
	 * \return Value of the pressure sensor.
	 */
	virtual double GetSensor(unsigned short iSpecies);

	/*!
	 * \brief Set the value of the undivided laplacian of the solution.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_undivided_laplacian - Value of the undivided solution for the index <i>val_var</i>.
	 */
	void SetUndivided_Laplacian(unsigned short val_var, double val_undivided_laplacian);

	/*!
	 * \brief Add the value of the undivided laplacian of the solution.
	 * \param[in] val_und_lapl - Value of the undivided solution.
	 */	
	void AddUnd_Lapl(double *val_und_lapl);

	/*!
	 * \brief Subtract the value of the undivided laplacian of the solution.
	 * \param[in] val_und_lapl - Value of the undivided solution.
	 */		
	void SubtractUnd_Lapl(double *val_und_lapl);

	/*!
	 * \brief Subtract the value of the undivided laplacian of the solution.
	 * \param[in] val_var - Variable of the undivided laplacian.
	 * \param[in] val_und_lapl - Value of the undivided solution.
	 */		
	void SubtractUnd_Lapl(unsigned short val_var, double val_und_lapl);

	/*!
	 * \brief Set the undivided laplacian of the solution to zero.
	 */			
	void SetUnd_LaplZero(void);

	/*!
	 * \brief Set a value to the undivided laplacian.
	 * \param[in] val_var - Variable of the undivided laplacian.
	 * \param[in] val_und_lapl - Value of the undivided laplacian.
	 */	
	void SetUnd_Lapl(unsigned short val_var, double val_und_lapl);

	/*!
	 * \brief Get the undivided laplacian of the solution.
	 * \return Pointer to the undivided laplacian vector.
	 */
	double *GetUndivided_Laplacian(void);

	/*!
	 * \brief Get the undivided laplacian of the solution.
	 * \param[in] val_var - Variable of the undivided laplacian.
	 * \return Value of the undivided laplacian vector.
	 */
	double GetUndivided_Laplacian(unsigned short val_var);

	/*!
	 * \brief A virtual member.
	 * \return Value of the flow density.
	 */
	virtual double GetDensity(void);

	/*!
	 * \brief A virtual member.
	 * \return Value of the flow density.
	 */
	virtual double GetDensity(unsigned short val_iSpecies);
  
  /*!
	 * \brief A virtual member.
   * \param[in] val_Species - Index of species s.
	 * \return Value of the mass fraction of species s.
	 */
	virtual double GetMassFraction(unsigned short val_Species);

	/*!
	 * \brief A virtual member.
	 * \return Value of the flow energy.
	 */	
	virtual double GetEnergy(void);

	/*!
	 * \brief A virtual member.
	 * \return Pointer to the force projection vector.
	 */
	virtual double *GetForceProj_Vector(void);

	/*!
	 * \brief A virtual member.
	 * \return Pointer to the objective function source.
	 */
	virtual double *GetObjFuncSource(void);

	/*!
	 * \brief A virtual member.
	 * \return Pointer to the internal boundary vector.
	 */
	virtual double *GetIntBoundary_Jump(void);

	/*!
	 * \brief A virtual member.
	 * \return Value of the eddy viscosity.
	 */		
	virtual double GetEddyViscosity(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the eddy viscosity.
	 */
	virtual double GetEddyViscosityInc(void);

	/*!
	 * \brief A virtual member.
	 * \return Value of the flow enthalpy.
	 */		
	virtual double GetEnthalpy(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the flow pressure.
	 */
	virtual double GetPressure(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the flow pressure.
	 */
	virtual double GetPressureInc(void);

	/*!
	 * \brief A virtual member.
	 * \return Value of the linearized pressure.
	 */		
	virtual double GetDeltaPressure(void);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_vector - Direction of projection.
	 * \return Value of the projected velocity.
	 */		
	virtual double GetProjVel(double *val_vector);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_vector - Direction of projection.
	 * \param[in] val_species - Index of the desired species.
	 * \return Value of the projected velocity.
	 */		
	virtual double GetProjVel(double *val_vector, unsigned short val_species);

	/*!
	 * \brief A virtual member.
	 * \return Value of the sound speed.
	 */		
	virtual double GetSoundSpeed(void);

	/*!
	 * \brief A virtual member.
	 * \return Value of the density for the incompressible flow.
	 */		
	virtual double GetDensityInc(void);

  /*!
	 * \brief A virtual member.
	 * \return Value of the levelset for the freesurface flows.
	 */
	virtual double GetLevelSet(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the distance for the freesurface flows.
	 */
	virtual double GetDistance(void);
  
	/*!
	 * \brief A virtual member.
	 * \return Value of the beta for the incompressible flow.
	 */		
	virtual double GetBetaInc2(void);

	/*!
	 * \brief A virtual member.
	 * \return Value of the temperature.
	 */		
	virtual double GetTemperature(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the vibrational-electronic temperature.
	 */
	virtual double GetTemperature_ve(void);
  
  /*!
   * \brief A virtual member -- Get the mixture specific heat at constant volume (trans.-rot.).
   * \return \f$\rho C^{t-r}_{v} \f$
   */
  virtual double GetRhoCv_tr(void);
  
  /*!
   * \brief A virtual member -- Get the mixture specific heat at constant volume (vib.-el.).
   * \return \f$\rho C^{v-e}_{v} \f$
   */
  virtual double GetRhoCv_ve(void);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the velocity for the dimension <i>val_dim</i>.
	 */
	virtual double GetVelocity(unsigned short val_dim);

	/*!
	 * \brief A virtual member.
	 * \return Norm 2 of the velocity vector.
	 */		
	virtual double GetVelocity2(void);

	/*!
	 * \brief A virtual member.
	 * \return Norm 2 of the velocity vector of Fluid val_species.
	 */	
	virtual double GetVelocity2(unsigned short val_species);

	/*!
	 * \brief A virtual member.
	 * \return The laminar viscosity of the flow.
	 */		
	virtual double GetLaminarViscosity(void);

	/*!
	 * \brief A virtual member.
	 * \return The laminar viscosity of the incompressible flow.
	 */		
	virtual double GetLaminarViscosityInc(void);

	/*!
	 * \brief A virtual member.
	 * \return The laminar viscosity of the flow.
	 */
	virtual double GetLaminarViscosity(unsigned short iSpecies);

  /*!
   * \brief A virtual member.
   * \return Value of the species diffusion coefficient.
   */
  virtual double* GetDiffusionCoeff(void);
  
  /*!
   * \brief A virtual member.
   * \return Value of the thermal conductivity (translational/rotational)
   */
  virtual double GetThermalConductivity(void);
  
  /*!
   * \brief A virtual member.
   * \return Value of the thermal conductivity (vibrational)
   */
  virtual double GetThermalConductivity_ve(void);

	/*!
	 * \brief A virtual member.
	 * \return Sets separation intermittency
	 */
	virtual void SetGammaSep(double gamma_sep);

	/*!
	 * \brief A virtual member.
	 * \return Sets separation intermittency
	 */
	virtual void SetGammaEff(void);

	/*!
	 * \brief A virtual member.
	 * \return Returns intermittency
	 */
	virtual double GetIntermittency();

	/*!
	 * \brief A virtual member.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the vorticity.
	 */		
	virtual double GetVorticity(unsigned short val_dim);

	/*!
	 * \brief A virtual member.
	 * \return Value of the rate of strain magnitude.
	 */
	virtual double GetStrainMag(void);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_ForceProj_Vector - Pointer to the force projection vector.
	 */		
	virtual void SetForceProj_Vector(double *val_ForceProj_Vector);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_SetObjFuncSource - Pointer to the objective function source.
	 */
	virtual void SetObjFuncSource(double *val_SetObjFuncSource);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_IntBoundary_Jump - Pointer to the interior boundary jump.
	 */		
	virtual void SetIntBoundary_Jump(double *val_IntBoundary_Jump);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_eddy_viscosity - Value of the eddy viscosity.
	 */		
	virtual void SetEddyViscosity(double eddy_visc);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] val_eddy_viscosity - Value of the eddy viscosity.
	 */
	virtual void SetEddyViscosityInc(double eddy_visc);

	/*!
	 * \brief A virtual member.
	 */		
	virtual void SetEnthalpy(void);
	
	/*!
	 * \brief A virtual member.
	 */		
	virtual bool SetPrimVar_Compressible(CConfig *config);
  
  /*!
	 * \brief A virtual member.
	 */
  virtual bool Cons2PrimVar(CConfig *config, double *U, double *V,
                            double *dPdU, double *dTdU,
                            double *dTvedU);
  /*!
	 * \brief A virtual member.
	 */
  virtual void Prim2ConsVar(CConfig *config, double *V, double *U);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual bool SetPrimVar_Compressible(double SharpEdge_Distance, bool check, CConfig *config);
	 
	/*!
	 * \brief A virtual member.
	 */		
	virtual bool SetPrimVar_Compressible(double eddy_visc, double turb_ke, CConfig *config);
	
	/*!
	 * \brief A virtual member.
	 */
	virtual double GetPrimVar(unsigned short val_var);
  
  /*!
	 * \brief A virtual member.
	 */
  virtual void SetPrimVar(unsigned short val_var, double val_prim);
  
  /*!
	 * \brief A virtual member.
	 */
  virtual void SetPrimVar(double *val_prim);

	/*!
	 * \brief A virtual member.
	 */
	virtual double *GetPrimVar(void);
	
	/*!
	 * \brief A virtual member.
	 */		
	virtual void SetDensityInc(double val_density);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual void SetPressureInc(void);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual void SetVelocityInc(void);

	/*!
	 * \brief A virtual member.
	 */		
	virtual void SetBetaInc2(double val_betainc2);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_phi - Value of the adjoint velocity.
	 */		
	virtual void SetPhi_Old(double *val_phi);

	/*!
	 * \brief A virtual member.
	 * \param[in] Gamma - Ratio of Specific heats
	 */
	virtual bool SetPressure(double Gamma);
  
	/*!
	 * \brief A virtual member.
	 * \param[in] Gamma - Ratio of Specific heats
	 */
	virtual bool SetPressure(CConfig *config);

	/*!
	 * \brief A virtual member.
	 */
	virtual bool SetPressure(double Gamma, double turb_ke);

	/*!
	 * \brief A virtual member.
	 */
	virtual void SetPressure(void);
  
  /*!
   * \brief Calculates vib.-el. energy per mass, \f$e^{vib-el}_s\f$, for input species (not including KE)
   */
  virtual double CalcEve(double *V, CConfig *config, unsigned short val_Species);
  
  /*!
   * \brief Calculates enthalpy per mass, \f$h_s\f$, for input species (not including KE)
   */
  virtual double CalcHs(double *V, CConfig *config, unsigned short val_Species);
  
  /*!
   * \brief Calculates enthalpy per mass, \f$Cv_s\f$, for input species (not including KE)
   */
  virtual double CalcCvve(double val_Tve, CConfig *config, unsigned short val_Species);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] config - Configuration settings
	 */
	virtual void CalcdPdU(double *V, CConfig *config, double *dPdU);
  
  /*!
   * \brief Set partial derivative of temperature w.r.t. density \f$\frac{\partial P}{\partial \rho_s}\f$
   */
  virtual void CalcdTdU(double *V, CConfig *config, double *dTdU);
  
  /*!
   * \brief Set partial derivative of temperature w.r.t. density \f$\frac{\partial P}{\partial \rho_s}\f$
   */
  virtual void CalcdTvedU(double *V, CConfig *config, double *dTdU);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual double *GetdPdU(void);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual double *GetdTdU(void);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual double *GetdTvedU(void);
  
  /*!
	 * \brief A virtual member.
	 */
	virtual bool SetDensity(void);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_velocity - Value of the velocity.
	 * \param[in] Gamma - Ratio of Specific heats
	 */		
	virtual void SetDeltaPressure(double *val_velocity, double Gamma);

	/*!
	 * \brief A virtual member.
	 * \param[in] Gamma - Ratio of specific heats.
	 */		
	virtual bool SetSoundSpeed(double Gamma);

	/*!
	 * \brief A virtual member.
	 * \param[in] config - Configuration parameters.
	 */		
	virtual bool SetSoundSpeed(CConfig *config);

	/*!
	 * \brief A virtual member.
	 */		
	virtual bool SetSoundSpeed(void);

	/*!
	 * \brief A virtual member.
	 * \param[in] Gas_Constant - Value of the Gas Constant
	 */		
	virtual bool SetTemperature(double Gas_Constant);
  
  /*!
	 * \brief Sets the vibrational electronic temperature of the flow.
	 * \return Value of the temperature of the flow.
	 */
  virtual bool SetTemperature_ve(double val_Tve);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] config - Configuration parameters.
	 */
	virtual bool SetTemperature(CConfig *config);

	/*!
	 * \brief A virtual member.
	 * \param[in] config - Configuration parameters.
	 */	
	virtual void SetPrimVar(CConfig *config);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] config - Configuration parameters.
	 */
	virtual void SetPrimVar(CConfig *config, double *Coord);
	
	/*!
	 * \brief A virtual member.
	 * \param[in] Temperature_Wall - Value of the Temperature at the wall
	 */
	virtual void SetWallTemperature(double Temperature_Wall);

	/*!
	 * \brief A virtual member.
	 * \param[in] Temperature_Wall - Value of the Temperature at the wall
	 */
	virtual void SetWallTemperature(double* Temperature_Wall);

	/*!
	 * \brief Set the thermal coefficient.
	 * \param[in] config - Configuration parameters.
	 */
	virtual void SetThermalCoeff(CConfig *config);

	/*!
	 * \brief A virtual member.
	 */
	virtual void SetVelocity(void);
  
	/*!
	 * \brief A virtual member.
	 */
  virtual void SetStress(unsigned short iVar, unsigned short jVar, double val_stress);
  
	/*!
	 * \brief A virtual member.
   
	 */
  virtual double **GetStress(void);
  
	/*!
	 * \brief A virtual member.
	 */
  virtual void SetVonMises_Stress(double val_stress);
  
	/*!
	 * \brief A virtual member.
   
	 */
  virtual double GetVonMises_Stress(void);
  
  /*!
	 * \brief A virtual member.
	 */
  virtual void SetFlow_Pressure(double val_pressure);
  
	/*!
	 * \brief A virtual member.
   
	 */
  virtual double GetFlow_Pressure(void);

	/*!
	 * \brief A virtual member.
	 */		
	virtual void SetVelocity2(void);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_velocity - Pointer to the velocity.
	 */
	virtual void SetVelocity_Old(double *val_velocity);
  
  /*!
	 * \brief A virtual member.
	 * \param[in] val_velocity - Pointer to the velocity.
	 */
	virtual void SetVelocityInc_Old(double *val_velocity);

	/*!
	 * \brief A virtual member.
	 * \param[in] config - Definition of the particular problem.	 
	 */	
	virtual void SetLaminarViscosity(CConfig *config);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_laminar_viscosity_inc - Value of the laminar viscosity (incompressible flows).
	 */		
	virtual void SetLaminarViscosityInc(double val_laminar_viscosity_inc);

	/*!
	 * \brief A virtual member.
	 */		
	virtual void SetVorticity(void);

	/*!
	 * \brief A virtual member.
	 */
	virtual void SetStrainMag(void);

	/*!
	 * \brief A virtual member.
	 */
	virtual void SetVelSolutionOldDVector(void);

	/*!
	 * \brief A virtual member.
	 */
	virtual void SetVelSolutionDVector(void);

	/*!
	 * \brief A virtual member.
	 */
	virtual void SetGradient_PrimitiveZero(unsigned short val_primvar);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value to add to the gradient of the primitive variables.
	 */
	virtual void AddGradient_Primitive(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value to subtract to the gradient of the primitive variables.
	 */
	virtual void SubtractGradient_Primitive(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the primitive variables gradient.
	 */
	virtual double GetGradient_Primitive(unsigned short val_var, unsigned short val_dim);

  /*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the primitive variables gradient.
	 */
	virtual double GetLimiter_Primitive(unsigned short val_var);
  
	/*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient.
	 */
	virtual void SetGradient_Primitive(unsigned short val_var, unsigned short val_dim, double val_value);

  /*!
	 * \brief A virtual member.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient.
	 */
	virtual void SetLimiter_Primitive(unsigned short val_var, double val_value);
  
	/*!
	 * \brief A virtual member.
	 * \return Value of the primitive variables gradient.
	 */
	virtual double **GetGradient_Primitive(void);
  
  /*!
	 * \brief A virtual member.
	 * \return Value of the primitive variables gradient.
	 */
	virtual double *GetLimiter_Primitive(void);

	/*!
	 * \brief Set the blending function for the blending of k-w and k-eps.
	 * \param[in] val_viscosity - Value of the vicosity.
	 * \param[in] val_density - Value of the density.
	 * \param[in] val_dist - Value of the distance to the wall.
	 */
	virtual void SetBlendingFunc(double val_viscosity, double val_dist, double val_density);

	/*!
	 * \brief Get the first blending function of the SST model.
	 */
	virtual double GetF1blending(void);

	/*!
	 * \brief Get the second blending function of the SST model.
	 */
	virtual double GetF2blending(void);

	/*!
	 * \brief Get the value of the cross diffusion of tke and omega.
	 */
	virtual double GetCrossDiff(void){ return 0.0; };

	/*!
	 * \brief Get the value of the eddy viscosity.
	 * \return the value of the eddy viscosity.
	 */
	virtual double GetmuT(void);

	/*!
	 * \brief Set the value of the eddy viscosity.
	 * \param[in] val_muT
	 */
	virtual void SetmuT(double val_muT);

	/*!
	 * \brief Add a value to the maximum eigenvalue for the inviscid terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the inviscid terms of the PDE.
	 * \param[in] iSpecies - Value of iSpecies to which the eigenvalue belongs
	 */
	virtual void AddMax_Lambda_Inv(double val_max_lambda, unsigned short iSpecies);

	/*!
	 * \brief Add a value to the maximum eigenvalue for the viscous terms of the PDE.
	 * \param[in] val_max_lambda - Value of the maximum eigenvalue for the viscous terms of the PDE.
	 * \param[in] iSpecies - Value of iSpecies to which the eigenvalue belongs
	 */
	virtual void AddMax_Lambda_Visc(double val_max_lambda, unsigned short iSpecies);

	/*!
	 * \brief A virtual member.
	 * \param[in] val_difflevelset - Value of the diff level set (value-target).
	 */	
	virtual void SetDiffLevelSet(double val_difflevelset);

	/*!
	 * \brief A virtual member.
	 */		
	virtual double GetDiffLevelSet(void);

	/*!
	 * \brief Set the Eddy Viscosity Sensitivity of the problem.
	 * \param[in] val_EddyViscSens - Eddy Viscosity Sensitivity.
	 */
	virtual void SetEddyViscSens(double *val_EddyViscSens, unsigned short numTotalVar);

	/*!
	 * \brief Get the Eddy Viscosity Sensitivity of the problem.
	 * \return Pointer to the Eddy Viscosity Sensitivity.
	 */
	virtual double *GetEddyViscSens(void);
  
  /*!
   * \brief A virtual member.  Retrieves index of species densities in the TNE2 solver.
   */
  virtual unsigned short GetRhosIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetRhoIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetPIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetTIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetTveIndex(void);
  
  /*!
	 * \brief Retrieves the value of the velocity index in the primitive variable vector.
	 * \param[in] iRho*u
	 */
  virtual unsigned short GetVelIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetHIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetAIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetRhoCvtrIndex(void);
  
  /*!
	 * \brief Retrieves the value of the species density in the primitive variable vector.
	 * \param[in] iRho_s
	 */
  virtual unsigned short GetRhoCvveIndex(void);
  
  /*!
	 * \brief A virtual member. Set the direct solution for the adjoint solver.
	 * \param[in] val_solution_direct - Value of the direct solution.
	 */
	virtual void SetSolution_Direct(double *val_solution_direct);
  
	/*!
	 * \brief A virtual member. Get the direct solution for the adjoint solver.
	 * \return Pointer to the direct solution vector.
	 */
	virtual double *GetSolution_Direct(void);
  
};

/*!
 * \class CBaselineVariable
 * \brief Main class for defining the variables of a baseline solution from a restart file (for output).
 * \author F. Palacios, T. Economon.
 * \version 1.2.0
 */
class CBaselineVariable : public CVariable {
public:
  
	/*!
	 * \brief Constructor of the class.
	 */
	CBaselineVariable(void);
  
	/*!
	 * \overload
	 * \param[in] val_solution - Pointer to the flow value (initialization value).
	 * \param[in] val_nVar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CBaselineVariable(double *val_solution, unsigned short val_nVar, CConfig *config);
  
	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CBaselineVariable(void);
  
};

/*! 
 * \class CEulerVariable
 * \brief Main class for defining the variables of the Euler's solver.
 * \ingroup Euler_Equations
 * \author F. Palacios.
 * \version 1.2.0
 */
class CEulerVariable : public CVariable {
protected:
	double Velocity2;			/*!< \brief Square of the velocity vector. */
	double *TS_Source;		/*!< \brief Time spectral source term. */
	double Precond_Beta;	/*!< \brief Low Mach number preconditioner value, Beta. */
  double *WindGust;           /*! < \brief Wind gust value */
  double *WindGustDer;        /*! < \brief Wind gust derivatives value */
  
	/*--- Primitive variable definition ---*/
	double *Primitive;	/*!< \brief Primitive variables (T,vx,vy,vz,P,rho,h,c) in compressible flows. */
	double **Gradient_Primitive;	/*!< \brief Gradient of the primitive variables (T,vx,vy,vz,P,rho). */
  double *Limiter_Primitive;    /*!< \brief Limiter of the primitive variables (T,vx,vy,vz,P,rho). */
  
public:
  
	/*!
	 * \brief Constructor of the class.
	 */
	CEulerVariable(void);
  
	/*!
	 * \overload
	 * \param[in] val_density - Value of the flow density (initialization value).
	 * \param[in] val_velocity - Value of the flow velocity (initialization value).
	 * \param[in] val_energy - Value of the flow energy (initialization value).
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nvar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CEulerVariable(double val_density, double *val_velocity, double val_energy, unsigned short val_nDim,
                 unsigned short val_nvar, CConfig *config);
  
	/*!
	 * \overload
	 * \param[in] val_solution - Pointer to the flow value (initialization value).
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nvar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CEulerVariable(double *val_solution, unsigned short val_nDim, unsigned short val_nvar, CConfig *config);
  
	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CEulerVariable(void);

	/*!
	 * \brief Set to zero the gradient of the primitive variables.
	 */
	void SetGradient_PrimitiveZero(unsigned short val_primvar);

	/*!
	 * \brief Add <i>val_value</i> to the gradient of the primitive variables.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value to add to the gradient of the primitive variables.
	 */
	void AddGradient_Primitive(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief Subtract <i>val_value</i> to the gradient of the primitive variables.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value to subtract to the gradient of the primitive variables.
	 */
	void SubtractGradient_Primitive(unsigned short val_var, unsigned short val_dim, double val_value);

	/*!
	 * \brief Get the value of the primitive variables gradient.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the primitive variables gradient.
	 */
	double GetGradient_Primitive(unsigned short val_var, unsigned short val_dim);
  
  /*!
	 * \brief Get the value of the primitive variables gradient.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the primitive variables gradient.
	 */
	double GetLimiter_Primitive(unsigned short val_var);

	/*!
	 * \brief Set the gradient of the primitive variables.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient.
	 */
	void SetGradient_Primitive(unsigned short val_var, unsigned short val_dim, double val_value);

  /*!
	 * \brief Set the gradient of the primitive variables.
	 * \param[in] val_var - Index of the variable.
	 * \param[in] val_dim - Index of the dimension.
	 * \param[in] val_value - Value of the gradient.
	 */
	void SetLimiter_Primitive(unsigned short val_var, double val_value);
  
	/*!
	 * \brief Get the value of the primitive variables gradient.
	 * \return Value of the primitive variables gradient.
	 */
	double **GetGradient_Primitive(void);
  
  /*!
	 * \brief Get the value of the primitive variables gradient.
	 * \return Value of the primitive variables gradient.
	 */
	double *GetLimiter_Primitive(void);

	/*!
	 * \brief Set the value of the pressure.
	 */
	bool SetPressure(double Gamma);

	/*!
	 * \brief Set the value of the speed of the sound.
	 * \param[in] Gamma - Value of Gamma.
	 */
	bool SetSoundSpeed(double Gamma);

	/*!
	 * \brief Set the value of the enthalpy.
	 */
	void SetEnthalpy(void);
	
	/*!
	 * \brief Set all the primitive variables for compressible flows.
	 */
	bool SetPrimVar_Compressible(CConfig *config);
	
	/*!
	 * \brief Get the primitive variables.
	 * \param[in] val_var - Index of the variable.
	 * \return Value of the primitive variable for the index <i>val_var</i>.
	 */
	double GetPrimVar(unsigned short val_var);
  
  /*!
	 * \brief Set the value of the primitive variables.
	 * \param[in] val_var - Index of the variable.
   * \param[in] val_var - Index of the variable.
	 * \return Set the value of the primitive variable for the index <i>val_var</i>.
	 */
	void SetPrimVar(unsigned short val_var, double val_prim);
  
  /*!
	 * \brief Set the value of the primitive variables.
	 * \param[in] val_prim - Primitive variables.
	 * \return Set the value of the primitive variable for the index <i>val_var</i>.
	 */
	void SetPrimVar(double *val_prim);

	/*!
	 * \brief Get the primitive variables of the problem.
	 * \return Pointer to the primitive variable vector.
	 */
	double *GetPrimVar(void);
	
	/*!
	 * \brief Set the value of the density for the incompressible flows.
	 */
	void SetDensityInc(double val_density);
  
  /*!
	 * \brief Set the value of the density for the incompressible flows.
	 */
	bool SetDensity(void);
  
  /*!
	 * \brief Set the value of the density for the incompressible flows.
	 */
	void SetPressureInc(void);
  
  /*!
	 * \brief Set the value of the density for the incompressible flows.
	 */
	void SetVelocityInc(void);

	/*!
	 * \brief Set the value of the beta coeffient for incompressible flows.
	 */
	void SetBetaInc2(double val_betainc2);

	/*!
	 * \brief Set the value of the temperature.
	 * \param[in] Gas_Constant - Value of Gas Constant
	 */
	bool SetTemperature(double Gas_Constant);

	/*!
	 * \brief Get the norm 2 of the velocity.
	 * \return Norm 2 of the velocity vector.
	 */
	double GetVelocity2(void);

	/*!
	 * \brief Get the flow pressure.
	 * \return Value of the flow pressure.
	 */
	double GetPressure(void);
  
  /*!
	 * \brief Get the flow pressure.
	 * \return Value of the flow pressure.
	 */
	double GetPressureInc(void);
  
	/*!
	 * \brief Get the speed of the sound.
	 * \return Value of speed of the sound.
	 */
	double GetSoundSpeed(void);

	/*!
	 * \brief Get the value of density for the incompressible flow
	 * \return Value of beta squared.
	 */
	double GetDensityInc(void);

  /*!
	 * \brief Get the value of levelset for the freesurface flows
	 * \return Value of beta squared.
	 */
	double GetLevelSet(void);
  
  /*!
	 * \brief Get the value of distance for the freesurface flows
	 * \return Value of beta squared.
	 */
	double GetDistance(void);
  
	/*!
	 * \brief Get the value of beta squared for the incompressible flow
	 * \return Value of beta squared.
	 */
	double GetBetaInc2(void);

	/*!
	 * \brief Get the enthalpy of the flow.
	 * \return Value of the enthalpy of the flow.
	 */
	double GetEnthalpy(void);

	/*!
	 * \brief Get the density of the flow.
	 * \return Value of the density of the flow.
	 */
	double GetDensity(void);

	/*!
	 * \brief Get the energy of the flow.
	 * \return Value of the energy of the flow.
	 */
	double GetEnergy(void);

	/*!
	 * \brief Get the temperature of the flow.
	 * \return Value of the temperature of the flow.
	 */
	double GetTemperature(void);

	/*!
	 * \brief Get the velocity of the flow.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the velocity for the dimension <i>val_dim</i>.
	 */
	double GetVelocity(unsigned short val_dim);

	/*!
	 * \brief Get the projected velocity in a unitary vector direction (compressible solver).
	 * \param[in] val_vector - Direction of projection.
	 * \return Value of the projected velocity.
	 */
	double GetProjVel(double *val_vector);

	/*!
	 * \brief Set the velocity vector from the solution.
	 * \param[in] val_velocity - Pointer to the velocity.
	 */	
	void SetVelocity(void);

	/*!
	 * \brief Set the velocity vector from the old solution.
	 * \param[in] val_velocity - Pointer to the velocity.
	 */		
	void SetVelocity_Old(double *val_velocity);
  
  /*!
	 * \brief Set the velocity vector from the old solution.
	 * \param[in] val_velocity - Pointer to the velocity.
	 */
	void SetVelocityInc_Old(double *val_velocity);

	/*!
	 * \brief Get the value of the preconditioner Beta.
	 * \return Value of the low Mach preconditioner variable Beta
	 */
	double GetPreconditioner_Beta();

	/*!
	 * \brief Set the value of the preconditioner Beta.
	 * \param[in] Value of the low Mach preconditioner variable Beta
	 */
	void SetPreconditioner_Beta(double val_Beta);

	/*!
	 * \brief Set the value of the magnetic field
	 * \param[in] Value of the magnetic field
	 */
	void SetMagneticField(double* val_B);

};

/*! 
 * \class CNSVariable
 * \brief Main class for defining the variables of the Navier-Stokes' solver.
 * \ingroup Navier_Stokes_Equations
 * \author F. Palacios.
 * \version 1.2.0
 */
class CNSVariable : public CEulerVariable {
private:
	double Prandtl_Lam;       /*!< \brief Laminar Prandtl number. */
	double Prandtl_Turb;      /*!< \brief Turbulent Prandtl number. */
	double Temperature_Ref;   /*!< \brief Reference temperature of the fluid. */
	double Viscosity_Ref;     /*!< \brief Reference viscosity of the fluid. */
	double Viscosity_Inf;     /*!< \brief Viscosity of the fluid at the infinity. */
	double Vorticity[3];		/*!< \brief Vorticity of the fluid. */
	double StrainMag;           /*!< \brief Magnitude of rate of strain tensor. */
public:
  
	/*!
	 * \brief Constructor of the class.
	 */
	CNSVariable(void);
  
	/*!
	 * \overload
	 * \param[in] val_density - Value of the flow density (initialization value).
	 * \param[in] val_velocity - Value of the flow velocity (initialization value).
	 * \param[in] val_energy - Value of the flow energy (initialization value).
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nvar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CNSVariable(double val_density, double *val_velocity,
              double val_energy, unsigned short val_nDim, unsigned short val_nvar, CConfig *config);
  
	/*!
	 * \overload
	 * \param[in] val_solution - Pointer to the flow value (initialization value).
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nvar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CNSVariable(double *val_solution, unsigned short val_nDim, unsigned short val_nvar, CConfig *config);
  
	/*!
	 * \brief Destructor of the class.
	 */
	~CNSVariable(void);

	/*!
	 * \brief Set the laminar viscosity.
	 */
	void SetLaminarViscosity(CConfig *config);

	/*!
	 * \overload
	 * \param[in] val_laminar_viscosity_inc - Value of the laminar viscosity (incompressible flows).
	 */
	void SetLaminarViscosityInc(double val_laminar_viscosity_inc);

	/*!
	 * \brief Set the vorticity value.
	 */
	void SetVorticity(void);

	/*!
	 * \brief Set the rate of strain magnitude.
	 */
	void SetStrainMag(void);

	/*!
	 * \overload
	 * \param[in] val_eddy_viscosity - Value of the eddy viscosity.
	 */
	void SetEddyViscosity(double eddy_visc);
  
  /*!
	 * \overload
	 * \param[in] val_eddy_viscosity - Value of the eddy viscosity.
	 */
	void SetEddyViscosityInc(double eddy_visc);

	/*!
	 * \brief Get the laminar viscosity of the flow.
	 * \return Value of the laminar viscosity of the flow.
	 */
	double GetLaminarViscosity(void);

	/*!
	 * \brief Get the laminar viscosity of the incompressible flow.
	 * \return Value of the laminar viscosity of the incompressible flow.
	 */
	double GetLaminarViscosityInc(void);

	/*!
	 * \brief Get the eddy viscosity of the flow.
	 * \return The eddy viscosity of the flow.
	 */
	double GetEddyViscosity(void);
  
  /*!
	 * \brief Get the eddy viscosity of the flow.
	 * \return The eddy viscosity of the flow.
	 */
	double GetEddyViscosityInc(void);

	/*!
	 * \brief Set the temperature at the wall
	 */
	void SetWallTemperature(double temperature_wall);

	/*!
	 * \brief Get the value of the vorticity.
	 * \param[in] val_dim - Index of the dimension.
	 * \return Value of the vorticity.
	 */	
	double GetVorticity(unsigned short val_dim);

	/*!
	 * \brief Get the value of the magnitude of rate of strain.
	 * \return Value of the rate of strain magnitude.
	 */
	double GetStrainMag(void);

	/*!
	 * \brief Set the value of pressure.
	 */
	bool SetPressure(double Gamma, double turb_ke);
	
	/*!
	 * \brief Set all the primitive variables for compressible flows
	 */
	bool SetPrimVar_Compressible(double eddy_visc, double turb_ke, CConfig *config);

};

/*! 
 * \class CTurbVariable
 * \brief Main class for defining the variables of the turbulence model.
 * \ingroup Turbulence_Model
 * \author A. Bueno.
 * \version 1.2.0
 */
class CTurbVariable : public CVariable {
protected:
	double muT;                /*!< \brief Eddy viscosity. */

public:
	/*!
	 * \brief Constructor of the class. 
	 */	
	CTurbVariable(void);

	/*!
	 * \overload
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nVar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CTurbVariable(unsigned short val_nDim, unsigned short val_nVar, CConfig *config);

	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CTurbVariable(void);

	/*!
	 * \brief Get the value of the eddy viscosity.
	 * \return the value of the eddy viscosity.
	 */
	double GetmuT();

	/*!
	 * \brief Set the value of the eddy viscosity.
	 * \param[in] val_muT - Value of the eddy viscosity.
	 */
	void SetmuT(double val_muT);
};

/*!
 * \class CTurbSAVariable
 * \brief Main class for defining the variables of the turbulence model.
 * \ingroup Turbulence_Model
 * \author A. Bueno.
 * \version 1.2.0
 */

class CTurbSAVariable : public CTurbVariable {
public:
	/*!
	 * \brief Constructor of the class.
	 */
	CTurbSAVariable(void);

	/*!
	 * \overload
	 * \param[in] val_nu_tilde - Turbulent variable value (initialization value).
	 * \param[in] val_muT  - The eddy viscosity
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nVar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.	 
	 */	
	CTurbSAVariable(double val_nu_tilde, double val_muT, unsigned short val_nDim, unsigned short val_nVar, CConfig *config);

	/*!
	 * \brief Destructor of the class. 
	 */
	~CTurbSAVariable(void);

};

/*! 
 * \class CTurbSSTVariable
 * \brief Main class for defining the variables of the turbulence model.
 * \ingroup Turbulence_Model
 * \author A. Bueno.
 * \version 1.2.0
 */

class CTurbSSTVariable : public CTurbVariable {
protected:
	double sigma_om2,
	beta_star;
	double F1,		/*!< \brief Menter blending function for blending of k-w and k-eps. */
	F2,		        /*!< \brief Menter blending function for stress limiter. */
	CDkw;           /*!< \brief Cross-diffusion. */
  
public:
	/*!
	 * \brief Constructor of the class.
	 */
	CTurbSSTVariable(void);

	/*!
	 * \overload
	 * \param[in] val_rho_kine - Turbulent variable value (initialization value).
	 * \param[in] val_rho_omega - Turbulent variable value (initialization value).
	 * \param[in] val_nDim - Number of dimensions of the problem.
	 * \param[in] val_nVar - Number of variables of the problem.
	 * \param[in] config - Definition of the particular problem.
	 */
	CTurbSSTVariable(double val_rho_kine, double val_rho_omega, double val_muT, unsigned short val_nDim, unsigned short val_nVar,
			double *constants, CConfig *config);

	/*!
	 * \brief Destructor of the class.
	 */
	~CTurbSSTVariable(void);

	/*!
	 * \brief Set the blending function for the blending of k-w and k-eps.
	 * \param[in] val_viscosity - Value of the vicosity.
	 * \param[in] val_dist - Value of the distance to the wall.
	 * \param[in] val_density - Value of the density.
	 */
	void SetBlendingFunc(double val_viscosity, double val_dist, double val_density);

	/*!
	 * \brief Get the first blending function.
	 */
	double GetF1blending(void);

	/*!
	 * \brief Get the second blending function.
	 */
	double GetF2blending(void);

	/*!
	 * \brief Get the value of the cross diffusion of tke and omega.
	 */
	double GetCrossDiff(void);
};

#include "variable_structure.inl"
