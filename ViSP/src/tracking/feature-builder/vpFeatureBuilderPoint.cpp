/****************************************************************************
 *
 * $Id: vpFeatureBuilderPoint.cpp,v 1.13 2008-02-01 15:11:39 fspindle Exp $
 *
 * Copyright (C) 1998-2006 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit.
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Conversion between tracker and visual feature point.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/


/*!
  \file vpFeatureBuilderPoint.cpp
  \brief  conversion between tracker
  and visual feature Point
*/
#include <visp/vpFeatureBuilder.h>
#include <visp/vpFeatureException.h>
#include <visp/vpException.h>


/*!
  Create a vpFeaturePoint thanks to a vpDot and the parameters of the camera.
  The vpDot contains only the pixel coordinates of the point in an image.
  Thus this method uses the camera parameters to compute the meter coordinates \f$ x \f$ and \f$ y \f$ in the image plan.
  Those coordinates are stored in the vpFeaturePoint.

  \warning It is not possible to compute the depth of the point \f$ Z \f$ in the camera frame thanks to a vpDot. 
  This coordinate is needed in vpFeaturePoint to compute the interaction matrix. So this value must be computed outside this function.

  \param s : Visual feature \f$(x, y)\f$ to initialize. Be
  aware, the 3D depth \f$Z\f$ requested to compute the interaction
  matrix is not initialized by this function.
  \param cam : The parameters of the camera used to acquire the image containing the vpDot.
  \param t : The vpDot used to create the vpFeaturePoint.

  The code below shows how to initialize a vpFeaturePoint visual
  feature. First, we initialize the \f$x,y\f$, and lastly we
  set the 3D depth \f$Z\f$ of the point which is generally the result
  of a pose estimation.

  \code
  vpImage<unsigned char> I; // Image container
  vpCameraParameters cam;   // Default intrinsic camera parameters
  vpDot dot;               // Dot tracker

  vpFeaturePoint s;    // Point feature
  ...
  // Tracking on the dot
  dot.track(I);

  // Initialize rho,theta visual feature
  vpFeatureBuilder::create(s, cam, dot);
  
  // A pose estimation is requested to initialize Z, the depth of the
  // point in the camera frame.
  double Z = 1; // Depth of the point in meters
  ....
  s.set_Z(Z);
  \endcode
*/
void vpFeatureBuilder::create(vpFeaturePoint &s,
			      const vpCameraParameters &cam,
			      const vpDot &d)
{
  try
  {
    double x=0, y=0;

    vpImagePoint cog;
    cog = d.getCog();

    vpPixelMeterConversion::convertPoint(cam, cog, x, y) ;

    s.set_x(x) ;
    s.set_y(y) ;
  }
  catch(...)
  {
    vpERROR_TRACE("Error caught") ;
    throw ;
  }
}


/*!
  Create a vpFeaturePoint thanks to a vpDot2 and the parameters of the camera.
  The vpDot2 contains only the pixel coordinates of the point in an image.
  Thus this method uses the camera parameters to compute the meter coordinates \f$ x \f$ and \f$ y \f$ in the image plan.
  Those coordinates are stored in the vpFeaturePoint.

  \warning It is not possible to compute the depth of the point \f$ Z \f$ in the camera frame thanks to a vpDot2. 
  This coordinate is needed in vpFeaturePoint to compute the interaction matrix. So this value must be computed outside this function.

  \param s : The feature point.
  \param cam : The parameters of the camera used to acquire the image containing the vpDot2.
  \param t : The vpDot2 used to create the vpFeaturePoint.

  The code below shows how to initialize a vpFeaturePoint visual
  feature. First, we initialize the \f$x,y\f$, and lastly we
  set the 3D depth \f$Z\f$ of the point which is generally the result
  of a pose estimation.

  \code
  vpImage<unsigned char> I; // Image container
  vpCameraParameters cam;   // Default intrinsic camera parameters
  vpDot2 dot;               // Dot tracker

  vpFeaturePoint s;    // Point feature
  ...
  // Tracking on the dot
  dot.track(I);

  // Initialize rho,theta visual feature
  vpFeatureBuilder::create(s, cam, dot);
  
  // A pose estimation is requested to initialize Z, the depth of the
  // point in the camera frame.
  double Z = 1; // Depth of the point in meters
  ....
  s.set_Z(Z);
  \endcode
*/
void vpFeatureBuilder::create(vpFeaturePoint &s,
			      const vpCameraParameters &cam,
			      const vpDot2 &d)
{
  try
  {
    double x=0, y=0;

    vpImagePoint cog;
    cog = d.getCog();

    vpPixelMeterConversion::convertPoint(cam, cog, x, y) ;

    s.set_x(x) ;
    s.set_y(y) ;
  }
  catch(...)
  {
    vpERROR_TRACE("Error caught") ;
    throw ;
  }
}


/*!
  Create a vpFeaturePoint thanks to a vpImagePoint and the parameters of the camera.
  The vpImagePoint contains only the pixel coordinates of the point in an image.
  Thus this method uses the camera parameters to compute the meter coordinates \f$ x \f$ and \f$ y \f$ in the image plan.
  Those coordinates are stored in the vpFeaturePoint.

  \warning It is not possible to compute the depth of the point \f$ Z \f$ in the camera frame thanks to a vpImagePoint. 
  This coordinate is needed in vpFeaturePoint to compute the interaction matrix. So this value must be computed outside this function.

  \param s : The feature point.
  \param cam : The parameters of the camera used to acquire the image containing the point.
  \param iP : The vpImagePoint used to create the vpFeaturePoint.

  The code below shows how to initialize a vpFeaturePoint visual
  feature. First, we initialize the \f$x,y\f$, and lastly we
  set the 3D depth \f$Z\f$ of the point which is generally the result
  of a pose estimation.

  \code
  vpImage<unsigned char> I; // Image container
  vpCameraParameters cam;   // Default intrinsic camera parameters
  vpImagePoint iP;               // the point in the image

  vpFeaturePoint s;    // Point feature
  ...
  // Set the point coordinates in the image (here the coordinates are given in the (i,j) frame
  iP.set_i(0);
  iP.set_j(0);

  // Initialize rho,theta visual feature
  vpFeatureBuilder::create(s, cam, iP);
  
  // A pose estimation is requested to initialize Z, the depth of the
  // point in the camera frame.
  double Z = 1; // Depth of the point in meters
  ....
  s.set_Z(Z);
  \endcode
*/
void vpFeatureBuilder::create(vpFeaturePoint &s,
			      const vpCameraParameters &cam,
			      const vpImagePoint &ip)
{
  try
  {
    double x=0, y=0;

    vpPixelMeterConversion::convertPoint(cam, ip, x, y) ;

    s.set_x(x) ;
    s.set_y(y) ;
  }
  catch(...)
  {
    vpERROR_TRACE("Error caught") ;
    throw ;
  }
}


/*!
  Create a vpFeaturePoint thanks to a vpPoint.
  This method uses the point coordinates \f$ x \f$ and \f$ y \f$ in the image plan to set the visual feature parameters. 
  The value of the depth \f$ Z \f$ in the camera frame is also computed thanks to the coordinates in the camera frame which are stored in vpPoint.

  \warning To be sure that the vpFeaturePoint is well initialized, you have to be sure that at least the point coordinates in the image plan and in the camera frame are computed and stored in the vpPoint.

  \param s : The feature point.
  \param t : The vpPoint used to create the vpFeaturePoint.
*/
void
vpFeatureBuilder::create(vpFeaturePoint &s, const vpPoint &p)
{
  try
  {
    s.set_x( p.get_x()) ;
    s.set_y( p.get_y()) ;

    s.set_Z( p.cP[2]/p.cP[3])  ;

    if (s.get_Z() < 0)
    {
      vpERROR_TRACE("Point is behind the camera ") ;
      std::cout <<"Z = " << s.get_Z() << std::endl ;

      throw(vpFeatureException(vpFeatureException::badInitializationError,
			       "Point is behind the camera ")) ;
    }

    if (fabs(s.get_Z()) < 1e-6)
    {
      vpERROR_TRACE("Point Z coordinates is null ") ;
      std::cout <<"Z = " << s.get_Z() << std::endl ;

      throw(vpFeatureException(vpFeatureException::badInitializationError,
			       "Point Z coordinates is null")) ;
    }

  }
  catch(...)
  {
    vpERROR_TRACE("Error caught") ;
    throw ;
  }
}


/*!
  Create a vpFeaturePoint thanks to a vpPoint. In this method noise is introduced during the initialization of the vpFeaturePoint.
  This method uses the point coordinates \f$ x \f$ and \f$ y \f$ in the image plan to set the visual feature parameters. 
  The value of the depth \f$ Z \f$ in the camera frame is also computed thanks to the coordinates in the camera frame which are stored in vpPoint.

  This function intends to introduce noise after the initialization of the parameters. Cartesian \f$(x,y)\f$ coordinates
  are first converted in pixel coordinates in the image using \e
  goodCam camera parameters. Then, the pixels coordinates of the point
  are converted back to cartesian coordinates \f$(x^{'},y^{'})\f$ using
  the noisy camera parameters \e wrongCam. These last parameters are stored in the vpFeaturePoint.

  \warning To be sure that the vpFeaturePoint is well initialized, you have to be sure that at least the point coordinates in the image plan and in the camera frame are computed and stored in the vpPoint.

  \param s : The feature point.

  \param goodCam : Camera parameters used to introduce noise. These
  parameters are used to convert cartesian coordinates of the point \e
  p in the image plane in pixel coordinates.

  \param wrongCam : Camera parameters used to introduce noise. These
  parameters are used to convert pixel coordinates of the point in
  cartesian coordinates of the point in the image plane.

  \param t : The vpPoint used to create the vpFeaturePoint.
*/
void
vpFeatureBuilder::create(vpFeaturePoint &s,
			 const vpCameraParameters &goodCam,
			 const vpCameraParameters &wrongCam,
			 const vpPoint &p)
{
  try
  {
    double x = p.p[0] ;
    double y = p.p[1] ;

    s.set_Z( p.cP[2]/p.cP[3])  ;

    double u=0, v=0;
    vpMeterPixelConversion::convertPoint(goodCam,x,y,u,v) ;
    vpPixelMeterConversion::convertPoint(wrongCam,u,v,x,y) ;


    s.set_x(x) ;
    s.set_y(y) ;
  }
  catch(...)
  {
    vpERROR_TRACE("Error caught") ;
    throw ;
  }
}





/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
