#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

// Load image
Mat loadImage(const string &path)
{
    return imread(path);
}

// Calculate brightness (mean grayscale value)
double calculateBrightness(const Mat &img)
{
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    return mean(gray)[0];
}

// Calculate colorfulness (similar to Hasler & Süsstrunk method)
double calculateColorfulness(const Mat &img)
{
    Mat bgr[3];
    split(img, bgr);

    Mat rg = abs(bgr[2] - bgr[1]);
    Mat yb = abs(0.5 * (bgr[2] + bgr[1]) - bgr[0]);

    Scalar rgMean, rgStd, ybMean, ybStd;
    meanStdDev(rg, rgMean, rgStd);
    meanStdDev(yb, ybMean, ybStd);

    double stdRoot = sqrt(pow(rgStd[0], 2) + pow(ybStd[0], 2));
    double meanRoot = sqrt(pow(rgMean[0], 2) + pow(ybMean[0], 2));

    return stdRoot + 0.3 * meanRoot;
}

// Assign to conveyor belt
char assignConveyor(double brightness, double colorfulness)
{

    // Transparent: bright and not colorful
    if (brightness > 60 && colorfulness < 30)
        return 'B';
    // Colorful: high colorfulness
    else if (colorfulness >= 30)
        return 'C';
    // Else: assume black
    else
        return 'A';
}

// Process a single image
void processImage(const string &imagePath)
{
    Mat img = loadImage(imagePath);
    if (img.empty())
    {
        cerr << "Failed to load: " << imagePath << endl;
        return;
    }

    double brightness = calculateBrightness(img);
    double colorfulness = calculateColorfulness(img);
    char belt = assignConveyor(brightness, colorfulness);

    cout << fs::path(imagePath).filename() << " => Conveyor Belt " << belt
         << " | Brightness: " << brightness
         << " | Colorfulness: " << colorfulness << endl;
}

// Process all images in a folder
void processFolder(const string &folderPath)
{
    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            string ext = entry.path().extension().string();
            if (ext == ".jpg" || ext == ".png" || ext == ".jpeg")
            {
                processImage(entry.path().string());
            }
        }
    }
}

int main()
{
    string basePath = "C:/Users/sajja/Desktop/ct/dataset";

    vector<string> categories = {"black", "transparent", "colorful"};
    for (const string &category : categories)
    {
        cout << "\nProcessing " << category << " images:\n";
        processFolder(basePath + "/" + category);
    }

    return 0;
}
