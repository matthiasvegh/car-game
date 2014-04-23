
#include <boost/math/constants/constants.hpp>

#include "Track.hpp"
#include "Car.hpp"
#include "drawUtil.hpp"
#include "mathUtil.hpp"
#include "PolygonTrackBuilder.hpp"

namespace car {

Track createCircleTrack() {

	using namespace boost::math::float_constants;

	Track track;
	const int circleResolution = 60;
	const int numberOfCheckpoints = 72;
	const float innerCircleRadius = 50.;
	const float outerCircleRadius = 60.;
	for ( int i = 0; i < circleResolution; ++i ) {
		track.addLine(Line2f(
					innerCircleRadius*std::cos((i-1)*2*pi/circleResolution),
					innerCircleRadius*std::sin((i-1)*2*pi/circleResolution),
					innerCircleRadius*std::cos((i)*2*pi/circleResolution),
					innerCircleRadius*std::sin((i)*2*pi/circleResolution)));
		track.addLine(Line2f(
					outerCircleRadius*std::cos((i-1)*2*pi/circleResolution),
					outerCircleRadius*std::sin((i-1)*2*pi/circleResolution),
					outerCircleRadius*std::cos((i)*2*pi/circleResolution),
					outerCircleRadius*std::sin((i)*2*pi/circleResolution)));
	}
	for ( int i = 0; i < numberOfCheckpoints; ++i ) {
		track.addCheckpoint(Line2f(
				innerCircleRadius*std::cos((i)*2*pi/numberOfCheckpoints),
				-innerCircleRadius*std::sin((i)*2*pi/numberOfCheckpoints),
				outerCircleRadius*std::cos((i)*2*pi/numberOfCheckpoints),
				-outerCircleRadius*std::sin((i)*2*pi/numberOfCheckpoints)
			));
	}

	track.setOrigin({0.f, 55.f}, 0.f);

	return track;
}

Track createZigZagTrack() {
	std::vector<sf::Vector2f> points;

	points.push_back({-55.f, 55.f});
	points.push_back({ 55.f, 55.f});
	points.push_back({-10.f,   0.f});
	points.push_back({ 55.f, -55.f});
	points.push_back({-55.f, -55.f});

	PolygonTrackBuilder builder{10.f, 5.f};
	return builder(points);
}

Track createCurvyTrack() {
	std::vector<sf::Vector2f> points;

	points.push_back({-55.f, 45.f});
	points.push_back({-45.f, 55.f});
	points.push_back({-30.f, 55.f});
	points.push_back({-15.f, 35.f});
	points.push_back({15.f, 35.f});
	points.push_back({45.f, 55.f});
	points.push_back({55.f, 45.f});
	points.push_back({55.f, -10.f});
	points.push_back({45.f, -45.f});
	points.push_back({-45.f, -45.f});

	PolygonTrackBuilder builder{5.f, 5.f};
	return builder(points);
}

Track createSilverstoneTrack() {

	std::vector<sf::Vector2f> points;

	points.push_back({556, 61});
	points.push_back({566, 62});
	points.push_back({579, 58});
	points.push_back({586, 63});
	points.push_back({947, 331});
	points.push_back({971, 349});
	points.push_back({982, 362});
	points.push_back({992, 386});
	points.push_back({996, 409});
	points.push_back({997, 435});
	points.push_back({993, 463});
	points.push_back({989, 492});
	points.push_back({985, 528});
	points.push_back({984, 551});
	points.push_back({985, 572});
	points.push_back({987, 588});
	points.push_back({991, 603});
	points.push_back({995, 614});
	points.push_back({1002, 627});
	points.push_back({1013, 641});
	points.push_back({1025, 655});
	points.push_back({1072, 713});
	points.push_back({1119, 771});
	points.push_back({1128, 782});
	points.push_back({1133, 791});
	points.push_back({1134, 799});
	points.push_back({1134, 809});
	points.push_back({1129, 819});
	points.push_back({1119, 828});
	points.push_back({1107, 833});
	points.push_back({1063, 847});
	points.push_back({1030, 858});
	points.push_back({1024, 860});
	points.push_back({1018, 867});
	points.push_back({1013, 877});
	points.push_back({1012, 885});
	points.push_back({1014, 893});
	points.push_back({1020, 899});
	points.push_back({1033, 907});
	points.push_back({1058, 917});
	points.push_back({1087, 927});
	points.push_back({1107, 932});
	points.push_back({1128, 935});
	points.push_back({1146, 937});
	points.push_back({1175, 939});
	points.push_back({1193, 937});
	points.push_back({1205, 929});
	points.push_back({1232, 899});
	points.push_back({1360, 755});
	points.push_back({1583, 502});
	points.push_back({1621, 458});
	points.push_back({1630, 447});
	points.push_back({1642, 426});
	points.push_back({1648, 410});
	points.push_back({1651, 393});
	points.push_back({1650, 370});
	points.push_back({1645, 357});
	points.push_back({1637, 344});
	points.push_back({1622, 336});
	points.push_back({1608, 333});
	points.push_back({1585, 331});
	points.push_back({1561, 329});
	points.push_back({1538, 327});
	points.push_back({1524, 322});
	points.push_back({1514, 315});
	points.push_back({1508, 307});
	points.push_back({1501, 296});
	points.push_back({1498, 286});
	points.push_back({1498, 275});
	points.push_back({1499, 262});
	points.push_back({1502, 252});
	points.push_back({1505, 245});
	points.push_back({1512, 237});
	points.push_back({1520, 230});
	points.push_back({1529, 225});
	points.push_back({1537, 222});
	points.push_back({1550, 220});
	points.push_back({1562, 221});
	points.push_back({1573, 223});
	points.push_back({1618, 245});
	points.push_back({1658, 264});
	points.push_back({1698, 285});
	points.push_back({1714, 294});
	points.push_back({1729, 304});
	points.push_back({1743, 314});
	points.push_back({1750, 320});
	points.push_back({1765, 337});
	points.push_back({1782, 358});
	points.push_back({1798, 381});
	points.push_back({1807, 402});
	points.push_back({1813, 421});
	points.push_back({1818, 445});
	points.push_back({1823, 482});
	points.push_back({1832, 561});
	points.push_back({1852, 758});
	points.push_back({1860, 846});
	points.push_back({1860, 869});
	points.push_back({1857, 885});
	points.push_back({1853, 898});
	points.push_back({1847, 912});
	points.push_back({1835, 927});
	points.push_back({1822, 938});
	points.push_back({1794, 952});
	points.push_back({1758, 965});
	points.push_back({1723, 976});
	points.push_back({1682, 988});
	points.push_back({1638, 998});
	points.push_back({1532, 1011});
	points.push_back({1476, 1015});
	points.push_back({1396, 1019});
	points.push_back({1353, 1022});
	points.push_back({1336, 1026});
	points.push_back({1313, 1034});
	points.push_back({1295, 1043});
	points.push_back({1282, 1051});
	points.push_back({1265, 1061});
	points.push_back({1252, 1068});
	points.push_back({1243, 1070});
	points.push_back({1229, 1070});
	points.push_back({1218, 1068});
	points.push_back({1205, 1065});
	points.push_back({1167, 1051});
	points.push_back({1122, 1036});
	points.push_back({1110, 1034});
	points.push_back({1096, 1034});
	points.push_back({1078, 1036});
	points.push_back({1065, 1040});
	points.push_back({1050, 1046});
	points.push_back({1039, 1053});
	points.push_back({1025, 1064});
	points.push_back({1011, 1075});
	points.push_back({993, 1084});
	points.push_back({980, 1088});
	points.push_back({967, 1090});
	points.push_back({951, 1089});
	points.push_back({937, 1085});
	points.push_back({925, 1080});
	points.push_back({917, 1073});
	points.push_back({908, 1064});
	points.push_back({896, 1049});
	points.push_back({884, 1029});
	points.push_back({870, 1007});
	points.push_back({854, 983});
	points.push_back({836, 964});
	points.push_back({823, 954});
	points.push_back({801, 943});
	points.push_back({753, 918});
	points.push_back({639, 859});
	points.push_back({353, 709});
	points.push_back({322, 694});
	points.push_back({291, 677});
	points.push_back({269, 665});
	points.push_back({245, 650});
	points.push_back({223, 635});
	points.push_back({202, 620});
	points.push_back({176, 603});
	points.push_back({158, 589});
	points.push_back({144, 576});
	points.push_back({129, 555});
	points.push_back({121, 536});
	points.push_back({118, 523});
	points.push_back({117, 508});
	points.push_back({118, 493});
	points.push_back({120, 482});
	points.push_back({124, 474});
	points.push_back({135, 457});
	points.push_back({144, 448});
	points.push_back({154, 440});
	points.push_back({164, 433});
	points.push_back({183, 422});
	points.push_back({208, 409});
	points.push_back({227, 399});
	points.push_back({259, 379});
	points.push_back({291, 355});
	points.push_back({331, 319});
	points.push_back({371, 283});
	points.push_back({443, 217});
	points.push_back({450, 210});
	points.push_back({453, 205});
	points.push_back({453, 198});
	points.push_back({451, 191});
	points.push_back({445, 183});
	points.push_back({431, 169});
	points.push_back({418, 154});
	points.push_back({415, 146});
	points.push_back({416, 137});
	points.push_back({418, 130});
	points.push_back({423, 122});
	points.push_back({430, 113});
	points.push_back({441, 102});
	points.push_back({457, 90});
	points.push_back({475, 77});
	points.push_back({494, 66});
	points.push_back({512, 59});
	points.push_back({524, 55});
	points.push_back({534, 53});
	points.push_back({545, 52});


	for(auto& point: points) {
		const auto scaleFactor = 6.f;
		point.x *= scaleFactor;
		point.y *= scaleFactor;
	}

	PolygonTrackBuilder builder{15.f, 50.f};

	//track width is presumably 15.
	return builder(points);
}

Car Track::createCar() const {
	return Car{startingPoint, startingDirection};
}

void Track::setOrigin(const sf::Vector2f& point, float direction) {
	startingPoint = point;
	startingDirection = direction;
}


void Track::addLine(const Line2f& line) {
	lines.push_back(line);
}

void Track::addCheckpoint(const Line2f& line) {
	checkpoints.push_back(line);
}


bool Track::collidesWith(const Line2f& line) const {
	for ( const Line2f& trackLine : lines ) {
		if ( intersects(line, trackLine) ) {
			return true;
		}
	}
	return false;
}

boost::optional<sf::Vector2f> Track::collideWithRay(const sf::Vector2f& origin, const sf::Vector2f& direction) const {
	float minimumDistanceSQ = -1.f; //negative distance means, we haven't found an intersecting line
	sf::Vector2f closest;
	for ( const Line2f& trackLine : lines ) {
		sf::Vector2f out;
		if ( intersectsRay(trackLine, origin, direction, &out) ) {
			float distanceSQ = getDistanceSQ(origin, out);
			if ( minimumDistanceSQ < 0.f || distanceSQ < minimumDistanceSQ ) {
				minimumDistanceSQ = distanceSQ;
				closest = out;
			}
		}
	}
	if ( minimumDistanceSQ < 0.f ) {
		return boost::none;
	}
	return closest;
}

int Track::checkpointCollidesWith(const Line2f& line) const {
	for ( std::size_t i = 0; i < checkpoints.size(); ++i ) {
		if ( intersects(line, checkpoints[i]) ) {
			return i;
		}
	}
	return -1;
}

std::size_t Track::getNumberOfCheckpoints() const {
	return checkpoints.size();
}

void Track::draw(sf::RenderWindow& window, int highlightCheckpoint) const {
	for ( const Line2f& trackLine : lines ) {
		drawLine(window, trackLine);
	}

	sf::Color checkpointColor{255, 255, 64};
	sf::Color highlightedCheckpointColor{128, 128, 255};

	for ( std::size_t i = 0; i < checkpoints.size(); ++i ) {

		drawLine(window, checkpoints[i],
				((static_cast<int>(i) == highlightCheckpoint) ?
						checkpointColor : highlightedCheckpointColor));
	}
}

namespace {

struct CheckedLine {
	bool start = false;
	bool end = false;
};

bool checkLineEndpoint(const sf::Vector2f& endpoint,
		const sf::Vector2f& intersection, float toleranceSquare,
		bool& alreadyChecked) {
	if (alreadyChecked ||
			getLengthSQ(sf::Vector2f{endpoint.x - intersection.x,
					endpoint.y - intersection.y}) > toleranceSquare) {
		return false;
	}

	alreadyChecked = true;
	return true;
}

}

void Track::check() const
{
	const float toleranceSquare = 0.0001;
	std::vector<CheckedLine> checkedLines(lines.size());

	for ( std::size_t i = 0; i < lines.size(); ++i ) {

		if (getLengthSQ(lines[i].start - lines[i].end) < toleranceSquare * 4) {
			throw TrackError{"Line segment too short"};
		}

		for ( std::size_t j = i + 1; j < lines.size(); ++j ) {
			sf::Vector2f p;
			if (intersects(lines[i], lines[j], &p)) {
				if (!(
						(checkLineEndpoint(lines[i].start, p, toleranceSquare,
								checkedLines[i].start) ||
						checkLineEndpoint(lines[i].end, p, toleranceSquare,
								checkedLines[i].end)) &&
						(checkLineEndpoint(lines[j].start, p, toleranceSquare,
								checkedLines[j].start) ||
						checkLineEndpoint(lines[j].end, p, toleranceSquare,
								checkedLines[j].end))
					)) {
					throw TrackError{"The track intersects with itself"};
				}
			}
		}
	}
}

}

