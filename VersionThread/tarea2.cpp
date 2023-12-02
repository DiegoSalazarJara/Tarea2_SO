#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void convertToGrayThreaded(cv::Mat& image, int num_threads) {
    // Obtener dimensiones de la imagen
    int rows = image.rows;
    int cols = image.cols;

    // Iniciar el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    // Crear threads
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    // Función lambda para procesar una parte de la imagen
    auto processChunk = [&](int startRow, int endRow) {
        for (int i = startRow; i < endRow; ++i) {
            for (int j = 0; j < cols; ++j) {
                cv::Vec3b color = image.at<cv::Vec3b>(i, j);
                int gray = 0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0];
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(gray, gray, gray);
            }
        }
    };

    int chunkSize = rows / num_threads;

    // Crear threads
    for (int t = 0; t < num_threads - 1; ++t) {
        int startRow = t * chunkSize;
        int endRow = startRow + chunkSize;
        threads.emplace_back(processChunk, startRow, endRow);
    }

    // Procesar la última parte de la imagen
    processChunk((num_threads - 1) * chunkSize, rows);

    // Esperar a que todos los threads terminen
    for (std::thread& thread : threads) {
        thread.join();
    }

    // Detener el temporizador y calcular el tiempo transcurrido
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Imprimir el tiempo transcurrido en segundos
    std::cout << "Tiempo de ejecución con " << num_threads << " hilos: " << elapsed.count() << " segundos" << std::endl;
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

    // Solicitar al usuario el número de hilos
    int num_threads;
    std::cout << "Ingrese el número de hilos: ";
    std::cin >> num_threads;


    // Aplicar conversión a escala de grises con threads
    convertToGrayThreaded(originalImage, num_threads);

    // Solicitar al usuario el nombre para la imagen convertida
    std::string convertedImageName;
    std::cout << "Ingrese el nombre para la imagen convertida a escala de grises (con extensión): ";
    std::cin >> convertedImageName;

    // Guardar la imagen convertida a escala de grises
    cv::imwrite(convertedImageName, originalImage);

    std::cout << "Imagen convertida a escala de grises y guardada como '" << convertedImageName << "'.\n";

    return 0;
}
