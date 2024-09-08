#ifndef MEI_XING_MAP_INFO_H__
#define MEI_XING_MAP_INFO_H__

#include <stdint.h>
#include <string>
#include "nlohmann/json.hpp"

//位置消息
struct Av2Position
{
    uint32_t MessageType;
    uint32_t CyclicCounter;
    uint32_t PathIndex;
    uint32_t Offset;
    uint32_t PositionIndex;
    uint32_t PositionAge;
    uint32_t Speed;
    uint32_t RelativeHeading;
    uint32_t PositionProbability;
    uint32_t PositionConfidence;
    uint32_t CurrentLane;
    uint32_t Reserved;

    Av2Position(uint32_t _messageType = 0, uint32_t _cyclicCounter = 0, uint32_t _pathIndex = 0, uint32_t _offset = 0, uint32_t _positionIndex = 0, 
                uint32_t _positionAge = 0, uint32_t _speed = 0, uint32_t _relativeHeading = 0, uint32_t _positionProbability = 0, uint32_t _positionConfidence = 0,
                uint32_t _currentLane = 0, uint32_t _reserved = 0)
    {
        MessageType = _messageType;
        CyclicCounter = _cyclicCounter;
        PathIndex = _pathIndex;
        Offset = _offset;
        PositionIndex = _positionIndex;
        PositionAge = _positionAge;
        Speed = _speed;
        RelativeHeading = _relativeHeading;
        PositionProbability = _positionProbability;
        PositionConfidence = _positionConfidence;
        CurrentLane = _currentLane;
        Reserved = _reserved;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Av2Position, MessageType, CyclicCounter, PathIndex, Offset, PositionIndex, PositionAge, Speed, RelativeHeading, PositionProbability, PositionConfidence, CurrentLane, Reserved);
};

//路径消息
struct Av2Stub
{
    uint32_t MessageType;
    uint32_t CyclicCounter;
    bool Retransmission;
    uint32_t PathIndex;
    uint32_t Offset;
    uint32_t Update;
    uint32_t SubPathIndex;
    uint32_t TurnAngle;
    uint32_t RelativeProbability;
    uint32_t FunctionalRoadClass;
    uint32_t FormOfWay;
    uint32_t NumberOfLane;
    uint32_t NumberOfLaneOpposite;
    uint32_t ComplexIntersection;
    uint32_t RightOfWay;
    uint32_t PartOfCalculatedRoute;
    uint32_t LastStubAtOffset;

    Av2Stub(uint32_t _messageType = 0, uint32_t _cyclicCounter = 0, bool _retransmission = false, uint32_t _pathIndex = 0, uint32_t _offset = 0, 
            uint32_t _update = 0, uint32_t _subPathIndex = 0, uint32_t _turnAngle = 0, uint32_t _relativeProbability = 0, uint32_t _functionalRoadClass = 0,
            uint32_t _formOfWay = 0, uint32_t _numberOfLane = 0, uint32_t _numberOfLaneOpposite = 0, uint32_t _complexIntersection = 0, uint32_t _rightOfWay = 0,
            uint32_t _partOfCalculatedRoute = 0, uint32_t _lastStubAtOffset = 0)
    {
        MessageType = _messageType;
        CyclicCounter = _cyclicCounter;
        Retransmission = _retransmission;
        PathIndex = _pathIndex;
        Offset = _offset;
        Update = _update;
        SubPathIndex = _subPathIndex;
        TurnAngle = _turnAngle;
        RelativeProbability = _relativeProbability;
        FunctionalRoadClass = _functionalRoadClass;
        FormOfWay = _formOfWay;
        NumberOfLane = _numberOfLane;
        NumberOfLaneOpposite = _numberOfLaneOpposite;
        ComplexIntersection = _complexIntersection;
        RightOfWay = _rightOfWay;
        PartOfCalculatedRoute = _partOfCalculatedRoute;
        LastStubAtOffset = _lastStubAtOffset;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Av2Stub, MessageType, CyclicCounter, Retransmission, PathIndex, Offset, Update, SubPathIndex, TurnAngle, RelativeProbability, FunctionalRoadClass, FormOfWay, NumberOfLane,
    NumberOfLaneOpposite, ComplexIntersection, RightOfWay, PartOfCalculatedRoute, LastStubAtOffset);
};

//路段消息
struct Av2Segment
{
    uint32_t MessageType;
    uint32_t CyclicCounter;
    bool Retransmission;
    uint32_t PathIndex;
    uint32_t Offset;
    bool Update;
    uint32_t FunctionalRoadClass;
    uint32_t FormOfWay;
    uint32_t EffectiveSpeedLimit;
    uint32_t EffectiveSpeedLimitType;
    uint32_t NumberOfLane;
    uint32_t NumberOfLaneOpposite;
    uint32_t Tunnel;
    uint32_t Bridge;
    uint32_t DividedRoad;
    uint32_t BuiltupArea;
    uint32_t ComplexIntersection;
    uint32_t RelativeProbability;
    uint32_t PartOfCalculatedRoute;
    uint32_t Reserved;

    Av2Segment(uint32_t _messageType = 0, uint32_t _cyclicCounter = 0, bool _retransmission = false, uint32_t _pathIndex = 0, uint32_t _offset = 0, 
                bool _update = false,
                uint32_t _functionalRoadClass = 0, uint32_t _formOfWay = 0, uint32_t _effectiveSpeedLimit = 0, uint32_t _effectiveSpeedLimitType = 0,
                uint32_t _numberOfLane = 0, uint32_t _numberOfLaneOpposite = 0, uint32_t _tunnel = 0, uint32_t _bridge = 0, uint32_t _dividedRoad = 0,
                uint32_t _builtupArea = 0, uint32_t _complexIntersection = 0, uint32_t _relativeProbability = 0, uint32_t _partOfCalculatedRoute = 0, 
                uint32_t _reserved = 0)
    {
        MessageType = _messageType;
        CyclicCounter = _cyclicCounter;
        Retransmission = _retransmission;
        PathIndex = _pathIndex;
        Offset = _offset;
        Update = _update;
        FunctionalRoadClass = _functionalRoadClass;
        FormOfWay = _formOfWay;
        EffectiveSpeedLimit = _effectiveSpeedLimit;
        EffectiveSpeedLimitType = _effectiveSpeedLimitType;
        NumberOfLane = _numberOfLane;
        NumberOfLaneOpposite = _numberOfLaneOpposite;
        Tunnel = _tunnel;
        Bridge = _bridge;
        DividedRoad = _dividedRoad;
        BuiltupArea = _builtupArea;
        ComplexIntersection = _complexIntersection;
        RelativeProbability = _relativeProbability;
        PartOfCalculatedRoute = _partOfCalculatedRoute;
        Reserved = _reserved;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Av2Segment, MessageType, CyclicCounter, Retransmission, PathIndex, Offset, FunctionalRoadClass, FormOfWay, 
    EffectiveSpeedLimit, EffectiveSpeedLimitType, NumberOfLane, NumberOfLaneOpposite, Tunnel,
    Bridge, DividedRoad, BuiltupArea, ComplexIntersection, RelativeProbability, PartOfCalculatedRoute, Reserved);
};

//短属性消息
struct Av2ProfileShort
{
    uint32_t MessageType;
    uint32_t CyclicCounter;
    bool Retransmission;
    uint32_t PathIndex;
    uint32_t Offset;
    bool Update;
    uint32_t ProfileType;
    bool ControlPoint;
    uint32_t Value0;
    uint32_t Distance1;
    uint32_t Value1;
    uint32_t Accuracy;

    Av2ProfileShort(uint32_t _messageType = 0, uint32_t _cyclicCounter = 0, bool _retransmission = false, uint32_t _pathIndex = 0, uint32_t _offset = 0, 
                    bool _update = false, uint32_t _profileType = 0, bool _controlPoint = false, uint32_t _value0 = 0, uint32_t _distance1 = 0,
                    uint32_t _value1 = 0, uint32_t _accuracy = 0)
    {
        MessageType = _messageType;
        CyclicCounter = _cyclicCounter;
        Retransmission = _retransmission;
        PathIndex = _pathIndex;
        Offset = _offset;
        Update = _update;
        ProfileType = _profileType;
        ControlPoint = _controlPoint;
        Value0 = _value0;
        Distance1 = _distance1;
        Value1 = _value1;
        Accuracy = _accuracy;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Av2ProfileShort, MessageType, CyclicCounter, Retransmission, PathIndex, Offset, Update, ProfileType, 
    ControlPoint, Value0, Distance1, Value1, Accuracy);
};

//长属性消息
struct Av2ProfileLong
{
    uint32_t MessageType;
    uint32_t CyclicCounter;
    bool Retransmission;
    uint32_t PathIndex;
    uint32_t Offset;
    bool Update;
    uint32_t ProfileType;
    bool ControlPoint;
    uint32_t Value;

    Av2ProfileLong(uint32_t _messageType = 0, uint32_t _cyclicCounter = 0, bool _retransmission = false, uint32_t _pathIndex = 0, uint32_t _offset = 0, 
                    bool _update = false, uint32_t _profileType = 0, bool _controlPoint = false, uint32_t _value = 0)
    {
        MessageType = _messageType;
        CyclicCounter = _cyclicCounter;
        Retransmission = _retransmission;
        PathIndex = _pathIndex;
        Offset = _offset;
        Update = _update;
        ProfileType = _profileType;
        ControlPoint = _controlPoint;
        Value = _value;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Av2ProfileLong, MessageType, CyclicCounter, Retransmission, PathIndex, Offset, Update, ProfileType, ControlPoint, Value);
};

//元数据消息
struct Av2Metadata
{
    uint32_t MessageType;
    uint32_t CyclicCounter;
    uint32_t CountryCode;
    uint32_t RegionCode;
    uint32_t DrivingSide;
    uint32_t SpeedUnit;
    uint32_t MajorProtocolVersion;
    uint32_t MinorProtocolVersion;
    uint32_t MinorProtocolSubVersion;
    uint32_t HardwareVersion;
    uint32_t MapProvider;
    uint32_t MapVersionYear;
    uint32_t MapVersionQuarter;
    uint32_t Reserved;

    Av2Metadata(uint32_t _messageType = 0, uint32_t _cyclicCounter = 0, uint32_t _countryCode = 0, uint32_t _regionCode= 0, uint32_t _drivingSide = 0, 
                uint32_t _speedUnit = 0, uint32_t _majorProtocolVersion = 0, uint32_t _minorProtocolVersion = 0, uint32_t _minorProtocolSubVersion = 0,
                uint32_t _hardwareVersion = 0, uint32_t _mapProvider = 0, uint32_t _mapVersionYear = 0, uint32_t _mapVersionQuarter = 0, uint32_t _reserved = 0)
        {
            MessageType = _messageType;
            CyclicCounter = _cyclicCounter;
            CountryCode = _countryCode;
            RegionCode = _regionCode;
            DrivingSide = _drivingSide;
            SpeedUnit = _speedUnit;
            MajorProtocolVersion = _majorProtocolVersion;
            MinorProtocolVersion = _minorProtocolVersion;
            MinorProtocolSubVersion = _minorProtocolSubVersion;
            HardwareVersion = _hardwareVersion;
            MapProvider = _mapProvider;
            MapVersionYear = _mapVersionYear;
            MapVersionQuarter = _mapVersionQuarter;
            Reserved = _reserved;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Av2Metadata, MessageType, CyclicCounter, CountryCode, RegionCode, DrivingSide, SpeedUnit, 
                                   MajorProtocolVersion, MinorProtocolVersion, MinorProtocolSubVersion,
                                   HardwareVersion, MapProvider, MapVersionYear, MapVersionQuarter, Reserved);
};

#endif