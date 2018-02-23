#include <Joystick.h>
#include <SampleRobot.h>
#include <Talon.h>
#include <Timer.h>
#include <DigitalInput.h>
#include <ADXRS450_Gyro.h>
#include <Driverstation.h>
class Robot: public frc::SampleRobot {
public:
	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			if(m_stick.GetRawButton(6))
			{
				LM0.Set(m_stick.GetY() * -0.5);
				LM1.Set(m_stick.GetY() * -0.5);
				RM0.Set(m_stick.GetRawAxis(3) * 0.5);
				RM1.Set(m_stick.GetRawAxis(3) * 0.5);
			}
			else
			{
			LM0.Set(m_stick.GetY() * -0.3);
			LM1.Set(m_stick.GetY() * -0.3);
			RM0.Set(m_stick.GetRawAxis(3) * 0.3);
			RM1.Set(m_stick.GetRawAxis(3) * 0.3);
			}
			if(fabs(m_stick1.GetY()) < 0.2)
			{
				MElevate.Set(0);
			}
			else
			{
				if(!DI.Get())
				{
					MElevate.Set(m_stick1.GetY());
				}
				else
				{
					if(m_stick1.GetY() > 0)
					{
						MElevate.Set(0);
					}
					else
					{
						MElevate.Set(m_stick1.GetY());
					}
				}
			}
			if(fabs(m_stick1.GetRawAxis(3)) < 0.2)
			{
				MIntake.Set(0);
			}
			else
			{
				MIntake.Set(m_stick1.GetRawAxis(3));
			}
			if(m_stick.GetRawButton(5) && m_stick.GetRawButton(7))
			{
				MClimbing0.Set(-1);
			}
			else if(m_stick2.GetRawButton(5))
			{
				MClimbing0.Set(0.3);
				MClimbing1.Set(0.3);
			}
			else
			{
				MClimbing0.Set(0);
			}
			if(m_stick.GetRawButton(6) && m_stick.GetRawButton(8))
			{
				MClimbing1.Set(-1);
			}
			else
			{
				MClimbing1.Set(0);
			}
			//angle = jaiRow.GetAngle();
			//printf("angle=%f\n", angle);
			/*if(DI.Get())
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
			*/
			frc::Wait(kUpdatePeriod);  // Wait 5ms for the next update.
		}
	}


	frc::Joystick m_stick { 0 };
	frc::Joystick m_stick1 { 1 };
	frc::Joystick m_stick2 { 2 };
	frc::Talon LM0 { 0 };
	frc::Talon LM1 { 1 };
	frc::Talon RM0 { 2 };
	frc::Talon RM1 { 3 };
	frc::Talon MElevate { 4 };
	frc::Talon MIntake { 5 };
	frc::Talon MClimbing0 { 6 };
	frc::Talon MClimbing1 { 7 };
	frc::DigitalInput DI { 0 };
	frc::ADXRS450_Gyro jaiRow { };
	std::string gameData;


	void RobotInit()
	{
		jaiRow.Calibrate();
	}

	void freeze()
	{
		LM0.Set(0);
		LM1.Set(0);
		RM0.Set(0);
		RM1.Set(0);
	}

	void allStop()
	{
		LM0.Set(0);
		LM1.Set(0);
		RM0.Set(0);
		RM1.Set(0);
		MElevate.Set(0);
		MIntake.Set(0);
		MClimbing0.Set(0);
		MClimbing1.Set(0);
	}
	void Rswitch()
	{
		allStop();
		jaiRow.Reset();
		int oh = 0;
		float angle = 0;
		while(angle > -43)
		{
			angle = jaiRow.GetAngle();
			LM0.Set(0);
			LM1.Set(0);
			RM0.Set(-0.4);
			RM1.Set(-0.4);
			MElevate.Set(0.3);
		}
		jaiRow.Reset();
		oh = 0;
		while(oh < 12000)
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(0.5);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.4);
				LM1.Set(0.4);
				RM0.Set(-0.4);
				RM1.Set(-0.4);
			}
			if(angle > 2)
			{
				LM0.Set(0.4);
				LM1.Set(0.4);
				RM0.Set(-0.409);
				RM1.Set(-0.409);
			}
			if(angle < -2)
			{
				LM0.Set(0.409);
				LM1.Set(0.409);
				RM0.Set(-0.4);
				RM1.Set(-0.4);
			}
			oh++;
		}
		oh = 0;
		while(angle < 35)
		{
			angle = jaiRow.GetAngle();
			LM0.Set(0.4);
			LM1.Set(0.4);
			RM0.Set(0);
			RM1.Set(0);
			MElevate.Set(1);
		}
		MElevate.Set(0);
		while(oh < 43000)
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(0.3);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.25);
				LM1.Set(0.25);
				RM0.Set(-0.25);
				RM1.Set(-0.25);
			}
			if(angle > 2)
			{
				LM0.Set(0.25);
				LM1.Set(0.25);
				RM0.Set(-0.26);
				RM1.Set(-0.26);
			}
			if(angle < -2)
			{
				LM0.Set(0.26);
				LM1.Set(0.26);
				RM0.Set(-0.25);
				RM1.Set(-0.25);
			}
			oh++;
		}
		oh = 0;
		allStop();
		MIntake.Set(-0.5);
		Wait(0.75);
		MIntake.Set(0);
		LM0.Set(-0.35);
		LM1.Set(-0.35);
		RM0.Set(0.35);
		RM1.Set(0.35);
		MElevate.Set(-0.7);
		Wait(1);
		freeze();
		Wait(0.8);
		allStop();
	}

	void Rscale()
	{
		allStop();
		jaiRow.Reset();
		int oh = 0;
		float angle = 0;
		while(oh < 22000) //accelerate and full speed elevate!!!
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.3 + 0.000029545454*oh);
				LM1.Set(0.3 + 0.000029545454*oh);
				RM0.Set(-0.3 - 0.000029545454*oh);
				RM1.Set(-0.3 - 0.000029545454*oh);
			}
			if(angle > 2)
			{
				LM0.Set(0.3 + 0.000029545454*oh);
				LM1.Set(0.3 + 0.000029545454*oh);
				RM0.Set(-0.31 - 0.000029545454*oh);
				RM1.Set(-0.31 - 0.000029545454*oh);
			}
			if(angle < -2)
			{
				LM0.Set(0.31 + 0.000029545454*oh);
				LM1.Set(0.31 + 0.000029545454*oh);
				RM0.Set(-0.3 - 0.000029545454*oh);
				RM1.Set(-0.3 - 0.000029545454*oh);
			}
			oh++;
		}
		LM0.Set(0.95);
		LM1.Set(0.95);
		RM0.Set(-0.95);
		RM1.Set(-0.95);
		Wait(0.5);
		jaiRow.Reset();
		oh = 0;
		while(oh < 28000) //decelerate and full speed elevate!!!
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			MIntake.Set(0.2);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.95 - 0.000029545454*oh);
				LM1.Set(0.95 - 0.000029545454*oh);
				RM0.Set(-0.95 + 0.000029545454*oh);
				RM1.Set(-0.95 + 0.000029545454*oh);
			}
			if(angle > 2)
			{
				LM0.Set(0.9 - 0.000029545454*oh);
				LM1.Set(0.9 - 0.000029545454*oh);
				RM0.Set(-0.96 + 0.000029545454*oh);
				RM1.Set(-0.96 + 0.000029545454*oh);
			}
			if(angle < -2)
			{
				LM0.Set(0.96 - 0.000029545454*oh);
				LM1.Set(0.96 - 0.000029545454*oh);
				RM0.Set(-0.9 + 0.000029545454*oh);
				RM1.Set(-0.9 + 0.000029545454*oh);
			}
			oh++;
		}
		jaiRow.Reset();
		allStop();
		while(!DI.Get()) //slow the fuck down and jump outta this loop when the switch is touched
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.2);
				LM1.Set(0.2);
				RM0.Set(-0.2);
				RM1.Set(-0.2);
			}
			if(angle > 2)
			{
				LM0.Set(0.2);
				LM1.Set(0.2);
				RM0.Set(-0.22);
				RM1.Set(-0.22);
			}
			if(angle < -2)
			{
				LM0.Set(0.22);
				LM1.Set(0.22);
				RM0.Set(-0.2);
				RM1.Set(-0.2);
			}
		}
		allStop();
		Wait(0.2);
		oh = 0;
		MElevate.Set(0); //stop the elevator
		jaiRow.Reset();
		while(oh < 11000)
		{
			LM0.Set(-0.4);
			LM1.Set(-0.4);
			RM0.Set(-0.4);
			RM1.Set(-0.4);
			if(!DI.Get())
			{
				MElevate.Set(0.3);
			}
			else
			{
				MElevate.Set(0);
			}
			oh++;
		}
		MElevate.Set(0);
		MIntake.Set(-0.6); // shoot the block
		Wait(0.5);
		MIntake.Set(0); // stop shooting
		allStop();
		angle = jaiRow.GetAngle();
		while(angle > -111) //start to turn counterclockwise not that gently and continue putting down the elevator, have to modulate the speed of rotation to make sure that the robot will rotate to the designated angle, and at the same time, the elevator reaches the lowest point.
		{
			MElevate.Set(-1);
			LM0.Set(-0.3);
			LM1.Set(-0.3);
			RM0.Set(-0.3);
			RM1.Set(-0.3);
			angle = jaiRow.GetAngle();
		}
		allStop();
		MElevate.Set(-1);
		LM0.Set(0.2);
		LM1.Set(0.2);
		RM0.Set(-0.3);
		RM1.Set(-0.3);
		Wait(2);
		allStop();
		jaiRow.Reset();
		oh = 0;
		while(oh < 27000) //go forward and take in the block
		{
			MIntake.Set(1);
			angle = jaiRow.GetAngle();
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.3);
				LM1.Set(0.3);
				RM0.Set(-0.3);
				RM1.Set(-0.3);
			}
			if(angle > 2)
			{
				LM0.Set(0.3);
				LM1.Set(0.3);
				RM0.Set(-0.31);
				RM1.Set(-0.31);
			}
			if(angle < -2)
			{
				LM0.Set(0.31);
				LM1.Set(0.31);
				RM0.Set(-0.3);
				RM1.Set(-0.3);
			}
			oh++;
		}
		freeze();
	}

	void RRscaleswitch()
	{
		allStop();
		jaiRow.Reset();
		int oh = 0;
		float angle = 0;
		while(oh < 22000) //accelerate and full speed elevate!!!
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.3 + 0.000029545454*oh);
				LM1.Set(0.3 + 0.000029545454*oh);
				RM0.Set(-0.3 - 0.000029545454*oh);
				RM1.Set(-0.3 - 0.000029545454*oh);
			}
			if(angle > 2)
			{
				LM0.Set(0.3 + 0.000029545454*oh);
				LM1.Set(0.3 + 0.000029545454*oh);
				RM0.Set(-0.31 - 0.000029545454*oh);
				RM1.Set(-0.31 - 0.000029545454*oh);
			}
			if(angle < -2)
			{
				LM0.Set(0.31 + 0.000029545454*oh);
				LM1.Set(0.31 + 0.000029545454*oh);
				RM0.Set(-0.3 - 0.000029545454*oh);
				RM1.Set(-0.3 - 0.000029545454*oh);
			}
			oh++;
		}
		LM0.Set(0.95);
		LM1.Set(0.95);
		RM0.Set(-0.95);
		RM1.Set(-0.95);
		Wait(0.5);
		jaiRow.Reset();
		oh = 0;
		while(oh < 28000) //decelerate and full speed elevate!!!
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			MIntake.Set(0.2);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.95 - 0.000029545454*oh);
				LM1.Set(0.95 - 0.000029545454*oh);
				RM0.Set(-0.95 + 0.000029545454*oh);
				RM1.Set(-0.95 + 0.000029545454*oh);
			}
			if(angle > 2)
			{
				LM0.Set(0.9 - 0.000029545454*oh);
				LM1.Set(0.9 - 0.000029545454*oh);
				RM0.Set(-0.96 + 0.000029545454*oh);
				RM1.Set(-0.96 + 0.000029545454*oh);
			}
			if(angle < -2)
			{
				LM0.Set(0.96 - 0.000029545454*oh);
				LM1.Set(0.96 - 0.000029545454*oh);
				RM0.Set(-0.9 + 0.000029545454*oh);
				RM1.Set(-0.9 + 0.000029545454*oh);
			}
			oh++;
		}
		jaiRow.Reset();
		allStop();
		while(!DI.Get()) //slow the fuck down and jump outta this loop when the switch is touched
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.2);
				LM1.Set(0.2);
				RM0.Set(-0.2);
				RM1.Set(-0.2);
			}
			if(angle > 2)
			{
				LM0.Set(0.2);
				LM1.Set(0.2);
				RM0.Set(-0.22);
				RM1.Set(-0.22);
			}
			if(angle < -2)
			{
				LM0.Set(0.22);
				LM1.Set(0.22);
				RM0.Set(-0.2);
				RM1.Set(-0.2);
			}
		}
		allStop();
		Wait(0.2);
		oh = 0;
		MElevate.Set(0); //stop the elevator
		jaiRow.Reset();
		while(oh < 11000)
		{
			LM0.Set(-0.4);
			LM1.Set(-0.4);
			RM0.Set(-0.4);
			RM1.Set(-0.4);

			if(!DI.Get())
			{
				MElevate.Set(0.3);
			}
			else
			{
				MElevate.Set(0);
			}
			oh++;
		}
		MElevate.Set(0);
		MIntake.Set(-0.6); // shoot the block
		Wait(0.5);
		MIntake.Set(0); // stop shooting
		allStop();
		angle = jaiRow.GetAngle();
		while(angle > -101) //start to turn counterclockwise not that gently and continue putting down the elevator, have to modulate the speed of rotation to make sure that the robot will rotate to the designated angle, and at the same time, the elevator reaches the lowest point.
		{
			MElevate.Set(-1);
			LM0.Set(-0.3);
			LM1.Set(-0.3);
			RM0.Set(-0.3);
			RM1.Set(-0.3);
			angle = jaiRow.GetAngle();
		}
		allStop();
		MElevate.Set(-0.9);
		LM0.Set(0.2);
		LM1.Set(0.2);
		RM0.Set(-0.3);
		RM1.Set(-0.3);
		Wait(2.5);
		allStop();
		jaiRow.Reset();
		oh = 0;
		while(oh < 27000) //go forward and take in the block
		{
			MIntake.Set(1);
			angle = jaiRow.GetAngle();
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.3);
				LM1.Set(0.3);
				RM0.Set(-0.3);
				RM1.Set(-0.3);
			}
			if(angle > 2)
			{
				LM0.Set(0.3);
				LM1.Set(0.3);
				RM0.Set(-0.31);
				RM1.Set(-0.31);
			}
			if(angle < -2)
			{
				LM0.Set(0.31);
				LM1.Set(0.31);
				RM0.Set(-0.3);
				RM1.Set(-0.3);
			}
			oh++;
		}
		freeze();
		MIntake.Set(0.4);
		Wait(0.3);
		MIntake.Set(0);
		MElevate.Set(1);
		LM0.Set(-0.2);
		LM1.Set(-0.2);
		RM0.Set(0.2);
		RM1.Set(0.2);
		Wait(0.5); //go backward a little bit, full speed elevate
		freeze();
		Wait(1.3); //continue elevating
		allStop();
		LM0.Set(0.3);
		LM1.Set(0.3);
		RM0.Set(-0.3);
		RM1.Set(-0.3);
		Wait(0.7);
		freeze();
		MIntake.Set(-0.7);
		Wait(0.5);
		LM0.Set(-0.2);
		LM1.Set(-0.2);
		RM0.Set(0.2);
		RM1.Set(0.2);
		Wait(1);
		allStop();
		MElevate.Set(-1);
		Wait(1);
		allStop();
	}

	void Lswitch()
	{
		allStop();
		jaiRow.Reset();
		int oh = 0;
		float angle = 0;
		while(angle > -65)
		{
			angle = jaiRow.GetAngle();
			LM0.Set(0);
			LM1.Set(0);
			RM0.Set(-0.4);
			RM1.Set(-0.4);
			MElevate.Set(0.5);
		}
		jaiRow.Reset();
		oh = 0;
		while(oh < 38000)
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(0.5);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.5);
				LM1.Set(0.5);
				RM0.Set(-0.5);
				RM1.Set(-0.5);
			}
			if(angle > 2)
			{
				LM0.Set(0.5);
				LM1.Set(0.5);
				RM0.Set(-0.51);
				RM1.Set(-0.51);
			}
			if(angle < -2)
			{
				LM0.Set(0.51);
				LM1.Set(0.51);
				RM0.Set(-0.5);
				RM1.Set(-0.5);
			}
			oh++;
		}
		MElevate.Set(0);
		while(angle < 60)
		{
			angle = jaiRow.GetAngle();
			LM0.Set(0.4);
			LM1.Set(0.4);
			RM0.Set(0);
			RM1.Set(0);
		}
		oh = 0;
		while(oh < 40000)
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(0.3);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.25);
				LM1.Set(0.25);
				RM0.Set(-0.25);
				RM1.Set(-0.25);
			}
			if(angle > 2)
			{
				LM0.Set(0.25);
				LM1.Set(0.25);
				RM0.Set(-0.26);
				RM1.Set(-0.26);
			}
			if(angle < -2)
			{
				LM0.Set(0.26);
				LM1.Set(0.26);
				RM0.Set(-0.25);
				RM1.Set(-0.25);
			}
			oh++;
		}
		allStop();
		MIntake.Set(-0.5);
		Wait(0.75);
		MIntake.Set(0);
		LM0.Set(-0.35);
		LM1.Set(-0.35);
		RM0.Set(0.35);
		RM1.Set(0.35);
		MElevate.Set(-1);
		Wait(0.5);
		freeze();
		Wait(0.8);
		allStop();
		}

	void Lscale()
	{
		allStop();
		jaiRow.Reset();
		int oh = 0;
		float angle = 0;
		while(oh < 22000) //accelerate and full speed elevate!!!
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.3 + 0.000029545454*oh);
				LM1.Set(0.3 + 0.000029545454*oh);
				RM0.Set(-0.3 - 0.000029545454*oh);
				RM1.Set(-0.3 - 0.000029545454*oh);
			}
			if(angle > 2)
			{
				LM0.Set(0.3 + 0.000029545454*oh);
				LM1.Set(0.3 + 0.000029545454*oh);
				RM0.Set(-0.31 - 0.000029545454*oh);
				RM1.Set(-0.31 - 0.000029545454*oh);
			}
			if(angle < -2)
			{
				LM0.Set(0.31 + 0.000029545454*oh);
				LM1.Set(0.31 + 0.000029545454*oh);
				RM0.Set(-0.3 - 0.000029545454*oh);
				RM1.Set(-0.3 - 0.000029545454*oh);
			}
			oh++;
		}
		jaiRow.Reset();
		oh = 0;
		while(oh < 28000) //decelerate and full speed elevate!!!
		{
			angle = jaiRow.GetAngle();
			MElevate.Set(1);
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.95 - 0.000029545454*oh);
				LM1.Set(0.95 - 0.000029545454*oh);
				RM0.Set(-0.95 + 0.000029545454*oh);
				RM1.Set(-0.95 + 0.000029545454*oh);
			}
			if(angle > 2)
			{
				LM0.Set(0.9 - 0.000029545454*oh);
				LM1.Set(0.9 - 0.000029545454*oh);
				RM0.Set(-0.96 + 0.000029545454*oh);
				RM1.Set(-0.96 + 0.000029545454*oh);
			}
			if(angle < -2)
			{
				LM0.Set(0.96 - 0.000029545454*oh);
				LM1.Set(0.96 - 0.000029545454*oh);
				RM0.Set(-0.9 + 0.000029545454*oh);
				RM1.Set(-0.9 + 0.000029545454*oh);
			}
			oh++;
		}
		jaiRow.Reset();
		angle = jaiRow.GetAngle();
		while(angle > -90)
		{
			LM0.Set(0);
			LM1.Set(0);
			RM0.Set(-0.3);
			RM1.Set(-0.3);
			angle = jaiRow.GetAngle();
		}
		jaiRow.Reset();
		oh = 0;
		while(!DI.Get())
		{
			MElevate.Set(1);
			angle = jaiRow.GetAngle();
			if(angle < 2 && angle > -2)
			{
				LM0.Set(0.5);
				LM1.Set(0.5);
				RM0.Set(-0.5);
				RM1.Set(-0.5);
			}
			if(angle > 2)
			{
				LM0.Set(0.5);
				LM1.Set(0.5);
				RM0.Set(-0.51);
				RM1.Set(-0.51);
			}
			if(angle < -2)
			{
				LM0.Set(0.51);
				LM1.Set(0.51);
				RM0.Set(-0.5);
				RM1.Set(-0.5);
			}
			oh++;
		}
		allStop();
		angle = jaiRow.GetAngle();
		while(angle < 90)
		{
			LM0.Set(0.3);
			LM1.Set(0.3);
			RM0.Set(0);
			RM1.Set(0);
			angle = jaiRow.GetAngle();
		}
		allStop();
		MIntake.Set(-0.6);
		Wait(0.5);
		allStop();
	}

	void Autonomous()
	{
		printf("3blocks!!!\n");
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		jaiRow.Reset();
		if(gameData[0] == 'L' && gameData[1] == 'L') //LL
		{
			//Lswitch();
			//Lscale();
			//printf("LL\n");
		}
		if(gameData[0] == 'L' && gameData[1] == 'R') //LR
		{
			Lswitch();
			//Rscale();
			//printf("LR\n");
		}
		if(gameData[0] == 'R' && gameData[1] == 'L') //RL
		{
			Rswitch();
			//Lscale();
			//printf("RL\n");
		}
		if(gameData[0] == 'R' && gameData[1] == 'R') //RR
		{
			//printf("RR\n");
			//Rswitch();
			//Rscale();
			RRscaleswitch();
		}
		allStop();
	}
	static constexpr double kUpdatePeriod = 0.005;
};

START_ROBOT_CLASS(Robot)
