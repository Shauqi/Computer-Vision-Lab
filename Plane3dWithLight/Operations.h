
#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED


void rotateX(double basic_mat[], double theta)
{
    basic_mat[5]= cos(theta);
    basic_mat[6]= -sin(theta);
    basic_mat[9]= sin(theta);
    basic_mat[10]=cos(theta);
}

void rotateY(double basic_mat[], double theta)
{
    basic_mat[0]= cos(theta);
    basic_mat[2]= sin(theta);
    basic_mat[8]= -sin(theta);
    basic_mat[10]=cos(theta);
}

void rotateZ(double basic_mat[], double theta)
{
    basic_mat[0]=cos(theta);
    basic_mat[1]=-sin(theta);
    basic_mat[4]=sin(theta);
    basic_mat[5]=cos(theta);
}

void translate(double basic_mat[], double x, double y, double z)
{
    basic_mat[12]=x;
    basic_mat[13]=y;
    basic_mat[14]=z;
}

void scale(double basic_mat[], double factor){
    for(int i=0;i<11;i+=5)basic_mat[i]=factor;
    basic_mat[15]=1;
}

void scale(double basic_mat[], double factorX, double factorY, double factorZ){
    basic_mat[0]=factorX;
    basic_mat[5]=factorY;
    basic_mat[10]=factorZ;
    basic_mat[15]=1;
}


#endif // OPERATIONS_H_INCLUDED
