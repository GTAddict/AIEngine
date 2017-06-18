#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
//------------------------------------------------------------------------
//
//  Name:   Transformations.h
//
//  Desc:   Functions for converting 2D vectors between World and Local
//          space.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>

#include "Vec2.h"
#include "Mat3.h"


//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position, orientation and scale,
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------
inline std::vector<Vec2> WorldTransform(std::vector<Vec2> &points,
                                            const Vec2   &pos,
                                            const Vec2   &forward,
                                            const Vec2   &side,
                                            const Vec2   &scale)
{
	//copy the original vertices into the buffer about to be transformed
  std::vector<Vec2> TranVec2s = points;
  
  //create a transformation matrix
	Mat3 matTransform;
	
	//scale
  if ( (scale.mX != 1.0) || (scale.mY != 1.0) )
  {
	  matTransform.Scale(scale.mX, scale.mY);
  }

	//rotate
	matTransform.Rotate(forward, side);

	//and translate
	matTransform.Translate(pos.mX, pos.mY);
	
  //now transform the object's vertices
  matTransform.TransformVec2(TranVec2s);

  return TranVec2s;
}

//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position and  orientation
//  this function transforms the 2D vectors into the object's world space
//------------------------------------------------------------------------
inline std::vector<Vec2> WorldTransform(std::vector<Vec2> &points,
                                 const Vec2   &pos,
                                 const Vec2   &forward,
                                 const Vec2   &side)
{
	//copy the original vertices into the buffer about to be transformed
  std::vector<Vec2> TranVec2s = points;
  
  //create a transformation matrix
	Mat3 matTransform;

	//rotate
	matTransform.Rotate(forward, side);

	//and translate
	matTransform.Translate(pos.mX, pos.mY);
	
  //now transform the object's vertices
  matTransform.TransformVec2(TranVec2s);

  return TranVec2s;
}

//--------------------- PointToWorldSpace --------------------------------
//
//  Transforms a point from the agent's local space into world space
//------------------------------------------------------------------------
inline Vec2 PointToWorldSpace(const Vec2 &point,
                                    const Vec2 &AgentHeading,
                                    const Vec2 &AgentSide,
                                    const Vec2 &AgentPosition)
{
	//make a copy of the point
  Vec2 TransPoint = point;
  
  //create a transformation matrix
	Mat3 matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

	//and translate
	matTransform.Translate(AgentPosition.mX, AgentPosition.mY);
	
  //now transform the vertices
  matTransform.TransformVec2(TransPoint);

  return TransPoint;
}

//--------------------- VectorToWorldSpace --------------------------------
//
//  Transforms a vector from the agent's local space into world space
//------------------------------------------------------------------------
inline Vec2 VectorToWorldSpace(const Vec2 &vec,
                                     const Vec2 &AgentHeading,
                                     const Vec2 &AgentSide)
{
	//make a copy of the point
  Vec2 TransVec = vec;
  
  //create a transformation matrix
	Mat3 matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

  //now transform the vertices
  matTransform.TransformVec2(TransVec);

  return TransVec;
}


//--------------------- PointToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
inline Vec2 PointToLocalSpace(const Vec2 &point,
                             Vec2 &AgentHeading,
                             Vec2 &AgentSide,
                              Vec2 &AgentPosition)
{

	//make a copy of the point
  Vec2 TransPoint = point;
  
  //create a transformation matrix
  Mat3 matTransform;
  Mat3::Matrix matrix;

  double Tx = -AgentPosition.Dot(AgentHeading);
  double Ty = -AgentPosition.Dot(AgentSide);

  //create the transformation matrix
  matrix.m11 = AgentHeading.mX;		matrix.m12 = AgentSide.mX;
  matrix.m21 = AgentHeading.mY;		matrix.m22 = AgentSide.mY;
  matrix.m31 = Tx;					matrix.m32 = Ty;

  matTransform.SetMatrix(matrix);
	
  //now transform the vertices
  matTransform.TransformVec2(TransPoint);

  return TransPoint;
}

//--------------------- VectorToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
inline Vec2 VectorToLocalSpace(const Vec2 &vec,
                             const Vec2 &AgentHeading,
                             const Vec2 &AgentSide)
{ 

	//make a copy of the point
  Vec2 TransPoint = vec;
  
  //create a transformation matrix
	Mat3 matTransform;
	Mat3::Matrix matrix;

  //create the transformation matrix
  matrix.m11 = AgentHeading.mX; matrix.m12 = AgentSide.mX;
  matrix.m21 = AgentHeading.mY; matrix.m22 = AgentSide.mY;
	
  //now transform the vertices
  matTransform.SetMatrix(matrix);
  matTransform.TransformVec2(TransPoint);

  return TransPoint;
}

//-------------------------- Vec2DRotateAroundOrigin --------------------------
//
//  rotates a vector ang rads around the origin
//-----------------------------------------------------------------------------
inline void Vec2DRotateAroundOrigin(Vec2& v, double ang)
{
  //create a transformation matrix
  Mat3 mat;

  //rotate
  mat.Rotate(ang);
	
  //now transform the object's vertices
  mat.TransformVec2(v);
}

//------------------------ CreateWhiskers ------------------------------------
//
//  given an origin, a facing direction, a 'field of view' describing the 
//  limit of the outer whiskers, a whisker length and the number of whiskers
//  this method returns a vector containing the end positions of a series
//  of whiskers radiating away from the origin and with equal distance between
//  them. (like the spokes of a wheel clipped to a specific segment size)
//----------------------------------------------------------------------------
inline std::vector<Vec2> CreateWhiskers(unsigned int  NumWhiskers,
                                            double        WhiskerLength,
                                            double        fov,
                                            Vec2      facing,
                                            Vec2      origin)
{
  //this is the magnitude of the angle separating each whisker
  double SectorSize = fov/(double)(NumWhiskers-1);

  std::vector<Vec2> whiskers;
  Vec2 temp;
  double angle = -fov*0.5; 

  for (unsigned int w=0; w<NumWhiskers; ++w)
  {
    //create the whisker extending outwards at this angle
    temp = facing;
    Vec2DRotateAroundOrigin(temp, angle);
    whiskers.push_back(origin + temp * WhiskerLength);

    angle+=SectorSize;
  }

  return whiskers;
}


#endif