#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>

void convertToGraySequential(cv::Mat& image) {
    // Obtener dimensiones de la imagen
    int rows = image.rows;
    int cols = image.cols;

    // Iniciar el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    // Recorrer cada píxel y aplicar conversión a escala de grises
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            int gray = 0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0];
            image.at<cv::Vec3b>(i, j) = cv::Vec3b(gray, gray, gray);
        }
    }

    // Detener el temporizador y calcular el tiempo transcurrido
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Imprimir el tiempo transcurrido en segundos
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
}

int main() {
    // Solicitar el nombre de la imagen original
    std::cout << "Ingrese el nombre de la imagen original (con extensión): ";
    std::string originalImageName;
    std::cin >> originalImageName;

    // Leer la imagen original usando OpenCV
    cv::Mat originalImage = cv::imread(originalImageName, cv::IMREAD_COLOR);

    // Verificar si la imagen original se leyó correctamente
    if (!originalImage.data) {
        std::cerr << "Error al cargar la imagen original." << std::endl;
        return -1;
    }

    // Aplicar conversión a escala de grises de manera secuencial
    convertToGraySequential(originalImage);

    // Solicitar al usuario el nombre para la imagen convertida
    std::cout << "Ingrese el nombre para la imagen convertida a escala de grises (con extensión): ";
    std::string convertedImageName;
    std::cin >> convertedImageName;

    // Guardar la imagen convertida a escala de grises
    cv::imwrite(convertedImageName, originalImage);

    std::cout << "Imagen convertida a escala de grises y guardada como '" << convertedImageName << "'.\n";

    return 0;
}

