@page page_coordinate_system Coordinate System

#Coordinate system

This page describes how coordinate systems is defined in holo projects.

---

## Basics

In HoloMatic worldview, coordinate system is abstracted with two attributes: *type* and *parameters*.

*Type* indicates the nature of the coordinate system.

*parameter* is used to show more detailed information about the coordinate system. 
How *parameter* is defined depends on the coordinate system type.

## Codec

A 32-bit data is used to encode coordinate systems.

@f[
\begin{bytefield}[bitwidth=2.0em]{32}
  \bitheader{0-31} \\
  \bitbox{4}{type} & \bitbox{28}{parameters}
\end{bytefield}
@f]

The first 4 bits represent the coordinate system type. So at most 16 system types can be defined.

The following 28 bits data is used to store coodinate system parameters. Details about how these 28 bits is defined 
varies from different coordinate system types.

## Coordinate system types

The following coordinate system type are defined:

- **VEHICLE**: A collection of coordinate systems that are associated with vehicle body. 
- **WGS84**: World Geodetic System(1984), the latitude/longitude system.
- **UTM6**: Universal Transverse Mercator(6-degree sliced)
- **UTM3**: Universal Transverse Mercator(3-degree sliced)
- **DR**: Dead reckoning.
- **GCJ02**: GuoCeJu-02, the latitude/longitude system with mysterious offset.

### UTM coordinate system

See [Universal Transverse Mercator coordinate system](https://en.wikipedia.org/wiki/Universal_Transverse_Mercator_coordinate_system) 
for full UTM definition.

The UTM system divides the Earth into 60 zones, each 6° of longitude in width. 
Zone 1 covers longitude 180° to 174° W; zone numbering increases eastward to zone 60, 
which covers longitude 174°E to 180°. The polar regions south of 80°S and north of 84°N are excluded.

![UTM Zone](Coordinate/EarthSlicing.jpg)

Each UTM zone is projected to plane coordinate(6-degree sliced):

![UTM Zone Projection](Coordinate/UtmZone.jpg)

A position on the Earth is given by a UTM zone number and a coordinate pair in that zone. 
The *point of origin* of each UTM zone is the intersection of **equator** and **center meridian**. 

To avoid negate coordinate numbers, the center meridian of each zone is defined to coincide with 500,000 meters East. 
(The origin point is represented (500,000, 0)). 

In the northern hemisphere, positions are measured northwards from zero at the equator. 
(The real origin point of northern hemisphere is the intersection of **equator** and **500,000 meters west of center meridian**)

In the southern hemisphere, positions are made with equator assigned a value of 10,000,000 meters North. 
(The real origin point of southern hemisphere is the intersection of **10,000,000 meters south of equator** and  **500,000 meters west of center meridian**)

### DR coordinate system

The DR coordinate system is used for relative positioning. The absolute position described in this coordinate system is 
meaningless. Users should only use short-term position variance information extracted from this coordinate.

---

## Coordinate system parameters

A coordinate system may associate with one or more parameters to provide additional information about the system.

For instance there are lots of sensors mounted in a vehicle, each sensor will update data within its own coordinate.
Though these coordinates are of different systems, 
the relationship among these systems is fixed or these coordinate system are bounded with the vehicle location. 
So we can define sensor locations as parameter of the *VEHICLE* coordinate system type.

Another example is that for UTM coordinate system type, the world is splited into a number of zones. 
Each zone defines a coordinate system. So the zone number can be a parameter of a UTM coordinate system.


### Parameter for VEHICLE coordinate type.

Type of **VEHICLE** has only one parameter: *SensorId*.

@f[
\begin{bytefield}{32}
  \bitheader{0-31} \\
  \bitbox{4}{type} & \bitbox{28}{sensor\_id}
\end{bytefield}
@f]

@par

SensorId indicates a specific location/sensor in a vehicle. 
The definition of *SensorId* parameter is the same as ::SensorId_t. See ::SensorId_t for possible values.

### Parameter for WGS84 coordinate type.

Type of **WGS84** has no parameter.

@f[
\begin{bytefield}{32}
  \bitheader{0-31} \\
  \bitbox{4}{type} & \bitbox{28}{0}
\end{bytefield}
@f]

### Parameter for UTM6 and UTM3 coordinate type.

@f[
\begin{bytefield}{32}
  \bitheader{0-31} \\
  \bitbox{4}{type} & \bitbox{8}{offset\_x} & \bitbox{12}{offset\_y} & \bitbox{1}{S} & \bitbox{7}{zone\_id}
\end{bytefield}
@f]

Types of **UTM6** and **UTM3** coordiante have four parameters: *zone*, *South flag*, *offset_x* and *offset_y*.

@par

***zone_id*** is a 7 bit data indicating UTM zone number. For UTM3 coordinate type, value range is [1, 120].
For UTM6 coordinate type, value range is [1, 60]

@par

***S*** South flag is a bool flag indication if the coordinate is in south hemisphere.

@par

***offset_x*** is a 8 bit data indicating the origin offset in latitudinal direction. Value range is **[0, 255]**. 
See more details below.

@par

***offset_y*** is a 12 bit data indicating the origin offset in longitudinal direction. Value range is **[0, 4095]**.

@par

The Easting range of a UTM position is about 167,000 meters to 833,000 meters. 
The Northing range of a UTM position is from 0 meters to 10,000,000 meters.

In many applications a position shall be represented by two `float32_t` type data with only 7 significant digits.
`float32_t` type is unable to mark a UTM position in `centimeter` level precision.

The solution is provide a UTM position with offset. 
A UTM position may be represented by a `float32` type coordinate in `centimeter` precision 
and a offset against the UTM zone origin.

The offset value is defined by *offset_x* and *offset_y* in unit of 4096 meters. 
So the Easting offset range will be **[0, 1,044,480]** and Northing offset range will be **[0, 16,777,216]**.


For example, a float32 UTM position (1.01, 1.01) with offset (100, 1000) and 
a float64 UTM position (409601.01, 6096001.01) marks a same position in a UTM zone.

### Parameter for DR coordinate type

@f[
\begin{bytefield}{32}
  \bitheader{0-31} \\
  \bitbox{4}{type} & \bitbox{12}{reserved} & \bitbox{16}{version}
\end{bytefield}
@f]

DR coordinate has one parameter: *version*.

@par

***VERSION*** is a 16-bit increamental counter representing DR coordinate version.
The origin of DR coordinate might change and then the coordinate version must be changed to indicate change of origin.

