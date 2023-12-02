#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace cv;
using namespace std;

Mat convertToGrayscale(const Mat& image) {
    Mat grayscaleImage(image.rows, image.cols, CV_8UC1);

    #pragma omp parallel for
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            uchar grayValue = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
            grayscaleImage.at<uchar>(r, c) = grayValue;
        }
    }

    return grayscaleImage;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        cout << "Usa: ./<nombre_programa> <nombre_imagen_original> <nombre_imagen_escala_gris> <nums_hebras>" << endl;
        return 1;
    }

    string inputImageFile = argv[1];
    string outputImageFile = argv[2];
    int numThreads = atoi(argv[3]);

    Mat image = imread(inputImageFile, IMREAD_COLOR);
    if (image.empty()) {
        cout << "Error al cargar la imagen: " << inputImageFile << endl;
        return 1;
    }

    omp_set_num_threads(numThreads);

    double startTime = omp_get_wtime();
    Mat grayscaleImage = convertToGrayscale(image);
    double endTime = omp_get_wtime();

    imwrite(outputImageFile, grayscaleImage);

    cout << "Tiempo de ejecucion: " << endTime - startTime << " segundos." << endl;

    return 0;
}