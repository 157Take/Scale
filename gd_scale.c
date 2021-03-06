#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(const int argc,const char *argv[]){

  FILE *out,*in;
  gdImagePtr im,im_new;
  int width,height,i,j,color,r,g,b;
  double scale;
  int new_width, new_height;

  if(argv[1]==NULL||argv[2]==NULL||!strcmp(argv[1],argv[2])){
    printf("argument deficiency or excess\n");
    exit(-1);
  }

  if((in=fopen(argv[1],"r"))==NULL){
    printf("file cannot open : %s\n",argv[1]);
    exit(-1);
  }

  if((out=fopen(argv[2],"wb"))==NULL){
    printf("file cannot open : %s\n",argv[2]);
    exit(-1);
  }

  if(atof(argv[3]) == 0){
    printf("cannot scale by 0\n");
    return 0;
  }
  scale = atof(argv[3]);
  
  im = gdImageCreateFromJpeg(in);

  width=gdImageSX(im);
  height=gdImageSY(im);

  new_width=(int)(width*scale);
  new_height=(int)(height*scale);

  

  im_new= gdImageCreateTrueColor(new_width,new_height);

  for(i=0;i<new_width;i++){
    for(j=0;j<new_height;j++){
      double s,t;
      int s1,s2,s3,s4,t1,t2,t3,t4;
      int index1,index2,index3,index4;

      s=1/scale*i;
      t=1/scale*j; 
      
      s1=(int)s;t1=(int)t;
      s2=(int)s;t2=(int)t+1;
      s3=(int)s+1;t3=(int)t;
      s4=(int)s+1;t4=(int)t+1;

      index1=gdImageGetPixel(im,s1,t1);
      index2=gdImageGetPixel(im,s2,t2);
      index3=gdImageGetPixel(im,s3,t3);
      index4=gdImageGetPixel(im,s4,t4);

      r=(int)((s4-s)*(t4-t)*gdImageRed(im,index1)
	      +(s3-s)*(t-t3)*gdImageRed(im,index2)
	      +(s-s2)*(t2-t)*gdImageRed(im,index3)
	      +(s-s1)*(t-t1)*gdImageRed(im,index4));

      g=(int)((s4-s)*(t4-t)*gdImageGreen(im,index1)
	      +(s3-s)*(t-t3)*gdImageGreen(im,index2)
	      +(s-s2)*(t2-t)*gdImageGreen(im,index3)
	      +(s-s1)*(t-t1)*gdImageGreen(im,index4));

      b=(int)((s4-s)*(t4-t)*gdImageBlue(im,index1)
	      +(s3-s)*(t-t3)*gdImageBlue(im,index2)
	      +(s-s2)*(t2-t)*gdImageBlue(im,index3)
	      +(s-s1)*(t-t1)*gdImageBlue(im,index4));

      r = r > 255 ? 255 : (r < 0 ? 0 : r);
      g = g > 255 ? 255 : (g < 0 ? 0 : g);
      b = b > 255 ? 255 : (b < 0 ? 0 : b);

      color=gdImageColorExact(im_new,r,g,b);	
      gdImageSetPixel(im_new,i,j,color);
    }
  }
  
  gdImageJpeg(im_new,out,-1);

  fclose(in);
  fclose(out);

  return 0;
  
}
