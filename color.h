/*const unsigned short 无符号短型常量类型*/

void color(const unsigned short color_Const) 
 { 


	if(color_Const>=1&&color_Const<=15){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_Const);
	}



	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	}
	


}
