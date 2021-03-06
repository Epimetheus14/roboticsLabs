#pragma config(StandardModel, "EV3_REMBOT");

float currentAngle;
float desiredAngle;
float desiredRadian;
float leftAngularVel;
float rightAngularVel;
float Xr;
float A;
float diameter;
float l;



float getAngularVelRad(tMotor motor){
	float first;
	float second;
	first = getMotorEncoder(motor);
	sleep(10);
	second = getMotorEncoder(motor);
	float sign =  first-second;

	if (sign<0){
		return -((getMotorRPM(motor)*(2*PI))/60);
	}


	return ((getMotorRPM(motor)*(2*PI))/60);
}

void anglechange(){
	if(desiredAngle<0){
		setMotorSyncEncoder(leftMotor, rightMotor, 100, (desiredAngle*2), 80);

	}
	else{
		setMotorSyncEncoder(leftMotor, rightMotor, -100, (desiredAngle*2), 80);
	}
	sleep(1000);
}

task display(){
	while (true){
		leftAngularVel = getAngularVelRad(leftMotor);
		rightAngularVel =getAngularVelRad(rightMotor);


		Xr = (diameter/2)*(rightAngularVel+leftAngularVel);
		A = (diameter/(2*l))*(rightAngularVel-leftAngularVel);


		displayTextLine(0, "leftVel: %f", leftAngularVel);
		displayTextLine(2, "rightVel: %f", rightAngularVel);
		displayTextLine(5,"Desired Angle: %d",desiredAngle);
		displayTextLine(7,"Current Angle: %d",currentAngle);
		displayTextLine(9,"the error %d",desiredAngle-currentAngle);
		displayTextLine(10, "A: %f", A);
		displayTextLine(12, "Xr: %f", Xr);

	}
}
task go(){
	anglechange();
}

task updateangle(){
	while(true){
		currentAngle= getMotorEncoder(rightMotor)/2;
	}
}



task main(){

	diameter = 58;
	l = 60;

	currentAngle=0;
	//desiredRadian=-((2*PI)/3);
	desiredRadian=2*PI;
	desiredAngle= desiredRadian*180/PI;
	startTask(display, 10);
	startTask(go, 10);
	startTask(updateangle, 10);
	while(true){}
}
