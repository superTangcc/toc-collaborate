/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Jonas Latt
 *  Address: Rue General Dufour 24,  1211 Geneva 4, Switzerland 
 *  E-mail: jonas.latt@gmail.com
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public 
 *  License along with this program; if not, write to the Free 
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
*/

#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "core/dataFieldBase2D.h"
#include "colormaps.h"
#include <sstream>
#include <iomanip>
#include <vector>

namespace olb {

namespace graphics {

template<typename T>
class ImageWriter {
public:
    ImageWriter(std::string const& map);
    ImageWriter(std::string const& map, int colorRange_, int numColors_);
    void setMap(std::string const& map, int colorRange_, int numColors_);
    void writePpm(std::string const& fName,
                  ScalarFieldBase2D<T> const& field,
                  T minVal, T maxVal) const;
    void writeScaledPpm(std::string const& fName,
                        ScalarFieldBase2D<T> const& field) const;
    void writeGif(std::string const& fName,
                  ScalarFieldBase2D<T> const& field,
                  T minVal, T maxVal) const;
    void writeGif(std::string const& fName,
                  ScalarFieldBase2D<T> const& field,
                  T minVal, T maxVal, T sizeX, T sizeY) const;
    void writeScaledGif(std::string const& fName,
                        ScalarFieldBase2D<T> const& field) const;
    void writeScaledGif(std::string const& fName,
                        ScalarFieldBase2D<T> const& field,
                        T sizeX, T sizeY) const;
    void writeText(std::string const& fName,
                   ScalarFieldBase2D<T> const& field) const;
private:
    int colorRange, numColors;
    ColorMap<T> colorMap;
};


////////// Standalone functions ////////////////////////////////////////

inline std::string createFileName(std::string name, int number, int width) {
    std::stringstream fNameStream;
    fNameStream << name << std::setfill('0') << std::setw(width) << number;
    return fNameStream.str();
}

}  // namespace graphics

}  // namespace olb

#endif
