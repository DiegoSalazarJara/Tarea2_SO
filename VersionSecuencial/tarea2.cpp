#include <opencv2/opencv.hpp>

void convertToGraySequential(cv::Mat& image) {
    // Obtener dimensiones de la imagen
    int rows = image.rows;
    int cols = image.cols;

    // Recorrer cada píxel y aplicar conversión a escala de grises
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            int gray = 0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0];
            image.at<cv::Vec3b>(i, j) = cv::Vec3b(gray, gray, gray);
        }
    }
}

int main() {
    // Leer la imagen usando OpenCV
    cv::Mat image = cv::imread("photo.jpg", cv::IMREAD_COLOR);

    // Verificar si la imagen se leyó correctamente
    if (!image.data) {
        std::cerr << "Error al cargar la imagen." << std::endl;
        return -1;
    }

    // Aplicar conversión a escala de grises de manera secuencial
    convertToGraySequential(image);

    // Guardar la imagen resultante
    cv::imwrite("output_sequential.jpg", image);

    return 0;
}

