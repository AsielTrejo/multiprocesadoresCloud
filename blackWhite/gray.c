#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//#define NUM_THREADS 1


int main()
{ 

  for (int NUM_THREADS = 1; NUM_THREADS<10; ++NUM_THREADS){
    omp_set_num_threads(NUM_THREADS);

    FILE *image, *outputImage, *lecturas;
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;
    unsigned char xx[54];
    int cuenta = 0;

    image = fopen("f1b.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img4_dd.bmp","wb");    //Imagen transformada


    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18]; //Original
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22]; //Original
    //printf("largo img %li\n",alto);
    //printf("ancho img %li\n",ancho);

    unsigned char img[alto][ancho];

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));
    

  const double startTimeP = omp_get_wtime();
  //#pragma omp parallel
   // {
    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;

      ptr[cuenta] = pixel; //b
      //ptr[cuenta+1] = pixel; //g
      //ptr[cuenta+2] = pixel; //r
      cuenta++;

    }
    // }                                  

    //Grises
    int row=0;
    int column = 0;
    int auxcolumn=0;

    row=0;
    column = 0;
  #pragma omp parallel
    {
    #pragma omp for schedule(dynamic)     
    for (int i = 0; i < (alto*ancho); ++i) {
      fputc(ptr[i], outputImage);
      fputc(ptr[i], outputImage);
      fputc(ptr[i], outputImage);
    }
  }
  
    const double endTimeP = omp_get_wtime();
    printf("Tiempo paralelo es %lf  Thread %i  \n", (endTimeP - startTimeP),NUM_THREADS);
    free(ptr);  
    fclose(image);
    fclose(outputImage);
  }
  return 0;
}
