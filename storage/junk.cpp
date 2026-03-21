static void displayLine(Canvas * canvas, float incY) {
    //int centerX = canvas->width()
    //int centerY = canvas->height();

    //std::cout << centerX;

    for(int incX = 0; incX < canvas->width(); incX++) {
        canvas->SetPixel(incX, incY, 255, 0, 0);
        usleep(10000);
    }

}