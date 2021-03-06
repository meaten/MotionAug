#pragma once

#include "anim/Character.h"
#include "anim/Motion.h"

class cKinCharacter : public cCharacter
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	struct tParams
	{
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		tParams();

		int mID;
		std::string mCharFile;
		std::string mMotionFile;
		std::string mMotionString;
		std::string mStateFile;
		tVector mOrigin;
		bool mLoadDrawShapes;

		std::vector<tVector> mGoalPos;
		std::vector<tVector> mCenter;
		std::vector<int> mIKJoint;
		std::vector<double> mPertitionTime;
		double mWindowTime;
	};

	cKinCharacter();
	virtual ~cKinCharacter();

	virtual bool Init(const tParams& params);
	virtual void Clear();
	virtual void Update(double time_step);
	virtual void Reset();

	virtual bool LoadMotion(const std::string& motion_file, const std::vector<tVector> GoalPos, const std::vector<tVector> Center, const std::vector<int> IKJoint, const std::vector<double> PertitionTime, const double WindowTime);
	virtual bool LoadMotion(const std::string& motion_string);
	virtual const cMotion& GetMotion() const;
	virtual double GetMotionDuration() const;
	virtual void SetMotionDuration(double dur);
	virtual void SetTime(double time);
	virtual double GetTime() const;
	virtual int GetCycle() const;
	virtual double GetPhase() const;

	virtual void Pose(double time);
	virtual void BuildAcc(Eigen::VectorXd& out_acc) const;
	
	virtual bool HasMotion() const;

	virtual void SetRootPos(const tVector& pos);
	virtual void SetRootRotation(const tQuaternion& q);

	virtual const tVector& GetOriginPos() const;
	virtual void SetOriginPos(const tVector& origin);
	virtual void MoveOrigin(const tVector& delta);
	virtual const tQuaternion& GetOriginRot() const;
	virtual void SetOriginRot(const tQuaternion& rot);
	virtual void RotateOrigin(const tQuaternion& rot);

	virtual tVector GetRootAngVel() const;

	virtual void CalcPose(double time, Eigen::VectorXd& out_pose) const;
	virtual void CalcVel(double time, Eigen::VectorXd& out_vel) const;
	virtual void CalcAcc(double time, Eigen::VectorXd& out_vel) const;

	virtual bool IsMotionOver() const;

	// motion processing methods
	virtual void BlendFrames(const cMotion::tFrame* a, const cMotion::tFrame* b, double lerp, cMotion::tFrame* out_frame) const;
	virtual void MirrorFrame(const std::vector<int>* right_joints, const std::vector<int>* left_joints, cMotion::tFrame* out_frame) const;
	virtual void CalcFrameVel(const cMotion::tFrame* a, const cMotion::tFrame* b, double timestep, cMotion::tFrame* out_vel) const;
	virtual void PostProcessFrame(cMotion::tFrame* out_frame) const;
	
	virtual tVector GetCycleRootDelta() const;

	virtual std::vector<double> CalcKeyframeTime(std::vector<int> end_effector);
	virtual std::vector<double> CalcPertitionTime(std::vector<int> IKjoints, std::vector<double> keyframe_time);
	virtual std::vector<int> ChooseIKjoints(std::vector<int> IKjoints, std::vector<double> keyframe_time);

protected:
	double mTime;
	cMotion mMotion;

	tVector mCycleRootDelta;
	tVector mOrigin;
	tQuaternion mOriginRot;

	virtual void ResetParams();
	virtual tVector CalcCycleRootDelta() const;
};