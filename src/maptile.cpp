#include "maptile.h"

#include <qcolor.h>
#include <qimage.h>

#include <cstddef>

#include "config.h"
#include "maptile.h"

QImage MapTile::createQuadChessTile(int width, const QColor &c1, const QColor &c2, int scale) {
    int scaledWidth = width * scale;
    QImage image(scaledWidth, scaledWidth, QImage::Format_RGB32);

    auto color1 = c1.rgb();
    auto color2 = c2.rgb();

    for (int y = 0; y < scaledWidth; ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(image.scanLine(y));
        int gridY = (y / scale) % width;
        int yParity = gridY & 1;
        for (int x = 0; x < scaledWidth; ++x) {
            int gridX = (x / scale) % width;
            line[x] = ((gridX & 1) ^ yParity) ? color2 : color1;
        }
    }

    return image;
}

QImage &MapTile::UNLOADED_REGION_TILE() {
    static QImage img = createQuadChessTile(2, QColor(128, 128, 128), QColor(148, 148, 148), cfg::RW << 3);
    return img;
}

QImage &MapTile::NULL_REGION_TILE() {
    static QImage img = createQuadChessTile(2, QColor(20, 20, 20), QColor(40, 40, 40), cfg::RW << 3);
    return img;
}

QImage MapTile::CREATE_REGION_TILE(std::bitset<cfg::RW * cfg::RW> chunk_bit_map, bool fill) {
    auto img = NULL_REGION_TILE().copy();
    if (fill) {
        int gridSize = img.width() / cfg::RW;
        QRgb red = qRgb(255, 0, 0);
        for (int y = 0; y < img.height(); ++y) {
            QRgb *line = (QRgb *)img.scanLine(y);
            int gridY = y / gridSize;
            for (int x = 0; x < img.width(); ++x) {
                int gridX = x / gridSize;
                if (chunk_bit_map[gridX * cfg::RW + gridY]) {
                    line[x] = red;
                }
            }
        }
    }
    return img;
}