/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, Jonas Latt
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


#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <vector>

namespace olb {

namespace IndexOrdering {
    typedef enum {forward, backward, memorySaving} OrderingT;
}

template<typename T>
struct DataSerializer {
    virtual ~DataSerializer() { }
    virtual size_t getSize() const =0;
    virtual const T* getNextDataBuffer(size_t& bufferSize) const =0;
    virtual bool isEmpty() const =0;
};

template<typename T>
struct DataUnSerializer {
    virtual ~DataUnSerializer() { }
    virtual size_t getSize() const =0;
    virtual T* getNextDataBuffer(size_t& bufferSize) =0;
    virtual void commitData() =0;
    virtual bool isFull() const =0;
};

template<typename T>
class ScalingSerializer : public DataSerializer<T> {
public:
    ScalingSerializer(DataSerializer<T> const& baseSerializer_, T scalingFactor_);
    virtual size_t getSize() const;
    virtual const T* getNextDataBuffer(size_t& bufferSize) const;
    virtual bool isEmpty() const;
private:
    DataSerializer<T> const& baseSerializer;
    mutable std::vector<T> scaledBuffer;
    T scalingFactor;
};

template<typename T, typename TConv>
class TypeConversionSerializer : public DataSerializer<TConv> {
public:
    TypeConversionSerializer(DataSerializer<T> const& baseSerializer_);
    virtual size_t getSize() const;
    virtual const TConv* getNextDataBuffer(size_t& bufferSize) const;
    virtual bool isEmpty() const;
private:
    DataSerializer<T> const& baseSerializer;
    mutable std::vector<TConv> convBuffer;
};

template<typename T>
struct Serializable {
    virtual ~Serializable() { };
    virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const =0;
    virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering) =0;
};

template<typename T>
void copySerializedData(DataSerializer<T> const& serializer, DataUnSerializer<T>& unSerializer);

template<typename T>
void copyDataBlock(Serializable<T> const& from, Serializable<T>& to,
                   IndexOrdering::OrderingT ordering = IndexOrdering::forward);

} // namespace olb

#endif
