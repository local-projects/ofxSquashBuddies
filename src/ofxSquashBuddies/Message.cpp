#include "Message.h"
#include "Constants.h"

namespace ofxSquashBuddies {
	//----------
	Message::Message() {

	}

	//----------
	Message::Message(const string & data) {
		this->setData(data);
	}

	//----------
	Message::Message(const void * data, size_t size) {
		this->setData(data, size);
	}

	//----------
	Message::Message(const ofPixels & data) {
		this->setData(data);
	}

	//----------
	Message::Message(const ofShortPixels & data) {
		this->setData(data);
	}

	//----------
	Message::Message(const ofFloatPixels & data) {
		this->setData(data);
	}

	//----------
	Message::Message(const ofMesh & data) {
		this->setData(data);
	}

	//----------
	Message::Message(const ofxKinectData & data) {
		this->setData(data);
	}
	
	//----------
	void Message::setData(const string & data) {
		this->setData(data.data(), data.size());
	}

	//----------
	void Message::setData(const void * data, size_t size) {
		this->headerAndBody.resize(size + sizeof(Header::String));

		auto & header = this->getHeader<Header::String>(true);
		auto body = this->getBodyData();
		memcpy(body, data, size);
	}

	//----------
	void Message::setData(const ofPixels & data) {
		const auto headerSize = sizeof(Header::Pixels);
		const auto bodySize = data.size(); // inner payload

		this->headerAndBody.resize(headerSize + bodySize);

		auto & header = this->getHeader<Header::Pixels>(true);
		header.width = data.getWidth();
		header.height = data.getHeight();
		header.pixelFormat = data.getPixelFormat();

		auto body = this->getBodyData();
		memcpy(body, data.getData(), bodySize);
	}

	//----------
	void Message::setData(const ofShortPixels & data) {
		const auto headerSize = sizeof(Header::ShortPixels);
		const auto bodySize = data.size() * sizeof(uint16_t); // inner payload

		this->headerAndBody.resize(headerSize + bodySize);

		auto & header = this->getHeader<Header::ShortPixels>(true);
		header.width = data.getWidth();
		header.height = data.getHeight();
		header.pixelFormat = data.getPixelFormat();

		auto body = this->getBodyData();
		memcpy(body, data.getData(), bodySize);
	}

	//----------
	void Message::setData(const ofFloatPixels & data) {
		const auto headerSize = sizeof(Header::FloatPixels);
		const auto bodySize = data.size() * sizeof(float); // inner payload

		this->headerAndBody.resize(headerSize + bodySize);

		auto & header = this->getHeader<Header::FloatPixels>(true);
		header.width = data.getWidth();
		header.height = data.getHeight();
		header.pixelFormat = data.getPixelFormat();

		auto body = this->getBodyData();
		memcpy(body, data.getData(), bodySize);
	}

	//----------
	void Message::setData(const ofMesh & data) {
		const auto headerSize = sizeof(Header::Mesh);
		
		const auto verticesDataSize = data.getNumVertices() * sizeof(ofVec3f);
		const auto colorsDataSize = data.getNumColors() * sizeof(ofFloatColor);
		const auto normalsDataSize = data.getNumNormals() * sizeof(ofVec3f);
		const auto texCoordsDataSize = data.getNumTexCoords() * sizeof(ofVec2f);
		const auto indicesDataSize = data.getNumIndices() * sizeof(ofIndexType);

		const size_t bodySize = verticesDataSize + colorsDataSize + normalsDataSize + texCoordsDataSize + indicesDataSize;
		
		this->headerAndBody.resize(headerSize + bodySize);

		// header
		{
			auto & header = this->getHeader<Header::Mesh>(true);
			header.verticesSize = (uint32_t) data.getNumVertices();
			header.colorsSize = (uint32_t) data.getNumColors();
			header.normalsSize = (uint32_t) data.getNumNormals();
			header.texCoordsSize = (uint32_t) data.getNumTexCoords();
			header.indicesSize = (uint32_t) data.getNumIndices();

			header.primitiveMode = data.getMode();

			header.useColors = data.usingColors();
			header.useNormals = data.usingNormals();
			header.useTextures = data.usingTextures();
			header.useIndices = data.usingIndices();
		}

		// body
		{
			auto body = (uint8_t *) this->getBodyData();

			memcpy(body, data.getVerticesPointer(), verticesDataSize);
			body += verticesDataSize;

			memcpy(body, data.getColorsPointer(), colorsDataSize);
			body += colorsDataSize;

			memcpy(body, data.getNormalsPointer(), normalsDataSize);
			body += normalsDataSize;

			memcpy(body, data.getTexCoordsPointer(), texCoordsDataSize);
			body += texCoordsDataSize;

			memcpy(body, data.getIndexPointer(), indicesDataSize);
		}
	}

	//----------
	void Message::setData(const ofxKinectData & data) {
		const auto headerSize = sizeof(Header::KinectData);

		const auto verticesDataSize0 = data.vertices0.size() * sizeof(ofVec3f);
		const auto colorsDataSize0 = data.colors0.size() * sizeof(ofFloatColor);
		const auto jointsDataSize0 = data.joints0.size() * sizeof(ofVec3f);

		const auto verticesDataSize1 = data.vertices1.size() * sizeof(ofVec3f);
		const auto colorsDataSize1 = data.colors1.size() * sizeof(ofFloatColor);
		const auto jointsDataSize1 = data.joints1.size() * sizeof(ofVec3f);

		const auto verticesDataSize2 = data.vertices2.size() * sizeof(ofVec3f);
		const auto colorsDataSize2 = data.colors2.size() * sizeof(ofFloatColor);
		const auto jointsDataSize2 = data.joints2.size() * sizeof(ofVec3f);

		const auto verticesDataSize3 = data.vertices3.size() * sizeof(ofVec3f);
		const auto colorsDataSize3 = data.colors3.size() * sizeof(ofFloatColor);
		const auto jointsDataSize3 = data.joints3.size() * sizeof(ofVec3f);

		const auto verticesDataSize4 = data.vertices4.size() * sizeof(ofVec3f);
		const auto colorsDataSize4 = data.colors4.size() * sizeof(ofFloatColor);
		const auto jointsDataSize4 = data.joints4.size() * sizeof(ofVec3f);

		const auto verticesDataSize5 = data.vertices5.size() * sizeof(ofVec3f);
		const auto colorsDataSize5 = data.colors5.size() * sizeof(ofFloatColor);
		const auto jointsDataSize5 = data.joints5.size() * sizeof(ofVec3f);

		const size_t bodySize = verticesDataSize0 + colorsDataSize0 + jointsDataSize0 +
			verticesDataSize1 + colorsDataSize1 + jointsDataSize1 +
			verticesDataSize2 + colorsDataSize2 + jointsDataSize2 +
			verticesDataSize3 + colorsDataSize3 + jointsDataSize3 +
			verticesDataSize4 + colorsDataSize4 + jointsDataSize4 +
			verticesDataSize5 + colorsDataSize5 + jointsDataSize5;

		this->headerAndBody.resize(headerSize + bodySize);

		// header
		{
			auto & header = this->getHeader<Header::KinectData>(true);
			header.verticesSize0 = (uint32_t)data.vertices0.size();
			header.colorsSize0 = (uint32_t)data.colors0.size();
			header.jointsSize0 = (uint32_t)data.joints0.size();

			header.verticesSize1 = (uint32_t)data.vertices1.size();
			header.colorsSize1 = (int32_t)data.colors1.size();
			header.jointsSize1 = (uint32_t)data.joints1.size();

			header.verticesSize2 = (uint32_t)data.vertices2.size();
			header.colorsSize2 = (uint32_t)data.colors2.size();
			header.jointsSize2 = (uint32_t)data.joints2.size();

			header.verticesSize3 = (uint32_t)data.vertices3.size();
			header.colorsSize3 = (uint32_t)data.colors3.size();
			header.jointsSize3 = (uint32_t)data.joints3.size();

			header.verticesSize4 = (uint32_t)data.vertices4.size();
			header.colorsSize4 = (uint32_t)data.colors4.size();
			header.jointsSize4 = (uint32_t)data.joints4.size();

			header.verticesSize5 = (uint32_t)data.vertices5.size();
			header.colorsSize5 = (uint32_t)data.colors5.size();
			header.jointsSize5 = (uint32_t)data.joints5.size();


		}

		// body
		{
			auto body = (uint8_t *) this->getBodyData(); 

			memcpy(body, data.vertices0.data(), verticesDataSize0);
			body += verticesDataSize0;

			memcpy(body, data.colors0.data(), colorsDataSize0);
			body += colorsDataSize0;

			memcpy(body, data.joints0.data(), jointsDataSize0);
			body += jointsDataSize0;

			memcpy(body, data.vertices1.data(), verticesDataSize1);
			body += verticesDataSize1;

			memcpy(body, data.colors1.data(), colorsDataSize1);
			body += colorsDataSize1;

			memcpy(body, data.joints1.data(), jointsDataSize1);
			body += jointsDataSize1;


			memcpy(body, data.vertices2.data(), verticesDataSize2);
			body += verticesDataSize2;

			memcpy(body, data.colors2.data(), colorsDataSize2);
			body += colorsDataSize2;
			

			memcpy(body, data.joints2.data(), jointsDataSize2);
			body += jointsDataSize2;


			memcpy(body, data.vertices3.data(), verticesDataSize3);
			body += verticesDataSize3;

			memcpy(body, data.colors3.data(), colorsDataSize3);
			body += colorsDataSize3;

			memcpy(body, data.joints3.data(), jointsDataSize3);
			body += jointsDataSize3;


			memcpy(body, data.vertices4.data(), verticesDataSize4);
			body += verticesDataSize4;

			memcpy(body, data.colors4.data(), colorsDataSize4);
			body += colorsDataSize4;

			memcpy(body, data.joints4.data(), jointsDataSize4);
			body += jointsDataSize4;


			memcpy(body, data.vertices5.data(), verticesDataSize5);
			body += verticesDataSize5;

			memcpy(body, data.colors5.data(), colorsDataSize5);
			body += colorsDataSize5;

			memcpy(body, data.joints5.data(), jointsDataSize5);
		}
	}


	//----------
	void Message::clear() {
		this->headerAndBody.clear();
	}

	//----------
	bool Message::getData(string & data) const {
		if (this->hasHeader<Header::String>()) {
			auto header = this->getHeader<Header::String>();
			data.assign((char *) this->getBodyData(), this->getBodySize());
			return true;
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match String/Basic type";
			return false;
		}
	}

	//----------
	bool Message::getData(void * data, size_t & size) const {
		if (this->hasHeader<Header::String>()) {
			auto header = this->getHeader<Header::String>();
			auto bodySize = this->getBodySize();
			if (bodySize > size) {
				OFXSQUASHBUDDIES_ERROR << "Insufficient size in your buffer. Cannot get data";
				return false;
			}
			else {
				memcpy(data, this->getBodyData(), bodySize);
				size = bodySize;
				return true;
			}
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match String/Basic type";
			return false;
		}
	}

	//----------
	bool Message::getData(ofPixels & data) const {
		if (this->hasHeader<Header::Pixels>()) {
			const auto & header = this->getHeader<Header::Pixels>();
			auto bodySize = this->getBodySize();
			ofPixelFormat pixelFormat = (ofPixelFormat)header.pixelFormat;

			//reallocate if we need to
			if (data.getWidth() != header.width || data.getHeight() != header.height || data.getPixelFormat() != pixelFormat) {
				data.allocate(header.width, header.height, pixelFormat);
			}
			if (data.size() != bodySize) {
				OFXSQUASHBUDDIES_ERROR << "Message body is of wrong size to fill pixels. Maybe a bug in sender?";
				return false;
			}
			else {
				memcpy(data.getData(), this->getBodyData(), bodySize);
				return true;
			}
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match Pixels type";
			return false;
		}
	}

	//----------
	bool Message::getData(ofShortPixels & data) {
		if (this->hasHeader<Header::ShortPixels>()) {
			const auto & header = this->getHeader<Header::ShortPixels>();
			auto bodySize = this->getBodySize();
			ofPixelFormat pixelFormat = (ofPixelFormat)header.pixelFormat;

			//reallocate if we need to
			data.allocate(header.width, header.headerSize, pixelFormat);
			if (data.size() * sizeof(uint16_t) != bodySize) {
				OFXSQUASHBUDDIES_ERROR << "Message body is of wrong size to fill pixels. Maybe a bug in sender?";
				return false;
			}
			else {
				memcpy(data.getData(), this->getBodyData(), bodySize);
				return true;
			}
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match ShortPixels type";
			return false;
		}
	}

	//----------
	bool Message::getData(ofFloatPixels & data) {
		if (this->hasHeader<Header::FloatPixels>()) {
			const auto & header = this->getHeader<Header::FloatPixels>();
			auto bodySize = this->getBodySize();
			ofPixelFormat pixelFormat = (ofPixelFormat)header.pixelFormat;

			//reallocate if we need to
			data.allocate(header.width, header.height, pixelFormat);
			if (data.size() * sizeof(float) != bodySize) {
				OFXSQUASHBUDDIES_ERROR << "Message body is of wrong size to fill pixels. Maybe a bug in sender?";
				return false;
			}
			else {
				memcpy(data.getData(), this->getBodyData(), bodySize);
				return true;
			}
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match FloatPixels type";
			return false;
		}
	}

	//----------
	bool Message::getData(ofMesh & data) const {
		if (this->hasHeader<Header::Mesh>()) {
			const auto & header = this->getHeader<Header::Mesh>();
			auto bodySize = this->getBodySize();

			auto & vertices = data.getVertices();
			auto & colors = data.getColors();
			auto & normals = data.getNormals();
			auto & texCoords = data.getTexCoords();
			auto & indices = data.getIndices();

			//resize as needed
			vertices.resize(header.verticesSize);
			colors.resize(header.colorsSize);
			normals.resize(header.normalsSize);
			texCoords.resize(header.texCoordsSize);
			indices.resize(header.indicesSize);

			//data sizes
			const auto verticesDataSize = header.verticesSize * sizeof(ofVec3f);
			const auto colorsDataSize = header.colorsSize * sizeof(ofFloatColor);
			const auto normalsDataSize = header.normalsSize * sizeof(ofVec3f);
			const auto texCoordsDataSize = header.texCoordsSize * sizeof(ofVec2f);
			const auto indicesDataSize = header.indicesSize * sizeof(ofIndexType);

			//copy in data
			{
				auto body = (uint8_t *) this->getBodyData();

				memcpy(data.getVerticesPointer(), body, verticesDataSize);
				body += verticesDataSize;

				memcpy(data.getColorsPointer(), body, colorsDataSize);
				body += colorsDataSize;

				memcpy(data.getNormalsPointer(), body, normalsDataSize);
				body += normalsDataSize;

				memcpy(data.getTexCoordsPointer(), body, texCoordsDataSize);
				body += texCoordsDataSize;

				memcpy(data.getIndexPointer(), body, indicesDataSize);
				body += indicesDataSize;
			}

			//apply header
			{
				data.setMode((ofPrimitiveMode) header.primitiveMode);
				header.useColors ? data.enableColors() : data.disableColors();
				header.useNormals ? data.enableNormals() : data.disableNormals();
				header.useTextures ? data.enableTextures() : data.disableTextures();
			}

			return true;
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match Mesh type";
			return false;
		}

	}

	//----------
	bool Message::getData(ofxKinectData & data) const {
		
		if (this->hasHeader<Header::KinectData>()) {
			const auto & header = this->getHeader<Header::KinectData>();
			auto bodySize = this->getBodySize();

			auto & vertices0 = data.vertices0;
			auto & colors0 = data.colors0;
			auto & joints0 = data.joints0;

			auto & vertices1 = data.vertices1;
			auto & colors1 = data.colors1;
			auto & joints1 = data.joints1;

			auto & vertices2 = data.vertices2;
			auto & colors2 = data.colors2;
			auto & joints2 = data.joints2;

			auto & vertices3 = data.vertices3;
			auto & colors3 = data.colors3;
			auto & joints3 = data.joints3;

			auto & vertices4 = data.vertices4;
			auto & colors4 = data.colors4;
			auto & joints4 = data.joints4;

			auto & vertices5 = data.vertices5;
			auto & colors5 = data.colors5;
			auto & joints5 = data.joints5;

			//resize as needed
			vertices0.resize(header.verticesSize0);
			colors0.resize(header.colorsSize0);
			joints0.resize(header.jointsSize0);

			vertices1.resize(header.verticesSize1);
			colors1.resize(header.colorsSize1);
			joints1.resize(header.jointsSize1);

			vertices2.resize(header.verticesSize2);
			colors2.resize(header.colorsSize2);
			joints2.resize(header.jointsSize2);

			vertices3.resize(header.verticesSize3);
			colors3.resize(header.colorsSize3);
			joints3.resize(header.jointsSize3);

			vertices4.resize(header.verticesSize4);
			colors4.resize(header.colorsSize4);
			joints4.resize(header.jointsSize4);

			vertices5.resize(header.verticesSize5);
			colors5.resize(header.colorsSize5);
			joints5.resize(header.jointsSize5);

			//data sizes
			const auto verticesDataSize0 = header.verticesSize0 * sizeof(ofVec3f);
			const auto colorsDataSize0 = header.colorsSize0 * sizeof(ofFloatColor);
			const auto jointsDataSize0 = header.jointsSize0 * sizeof(ofVec3f);

			const auto verticesDataSize1 = header.verticesSize1 * sizeof(ofVec3f);
			const auto colorsDataSize1 = header.colorsSize1 * sizeof(ofFloatColor);
			const auto jointsDataSize1 = header.jointsSize1 * sizeof(ofVec3f);

			const auto verticesDataSize2 = header.verticesSize2 * sizeof(ofVec3f);
			const auto colorsDataSize2 = header.colorsSize2 * sizeof(ofFloatColor);
			const auto jointsDataSize2 = header.jointsSize2 * sizeof(ofVec3f);

			const auto verticesDataSize3 = header.verticesSize3 * sizeof(ofVec3f);
			const auto colorsDataSize3 = header.colorsSize3 * sizeof(ofFloatColor);
			const auto jointsDataSize3 = header.jointsSize3 * sizeof(ofVec3f);

			const auto verticesDataSize4 = header.verticesSize4 * sizeof(ofVec3f);
			const auto colorsDataSize4 = header.colorsSize4 * sizeof(ofFloatColor);
			const auto jointsDataSize4 = header.jointsSize4 * sizeof(ofVec3f);

			const auto verticesDataSize5 = header.verticesSize5 * sizeof(ofVec3f);
			const auto colorsDataSize5 = header.colorsSize5 * sizeof(ofFloatColor);
			const auto jointsDataSize5 = header.jointsSize5 * sizeof(ofVec3f);

			//copy in data
			{
				auto body = (uint8_t *) this->getBodyData();

				memcpy(data.vertices0.data(), body, verticesDataSize0);
				body += verticesDataSize0;

				memcpy(data.colors0.data(), body, colorsDataSize0);
				body += colorsDataSize0;

				memcpy(data.joints0.data(), body, jointsDataSize0);
				body += jointsDataSize0;


				memcpy(data.vertices1.data(), body, verticesDataSize1);
				body += verticesDataSize1;

				memcpy(data.colors1.data(), body, colorsDataSize1);
				body += colorsDataSize1;

				memcpy(data.joints1.data(), body, jointsDataSize1);
				body += jointsDataSize1;


				memcpy(data.vertices2.data(), body, verticesDataSize2);
				body += verticesDataSize2;

				memcpy(data.colors2.data(), body, colorsDataSize2);
				body += colorsDataSize2;

				memcpy(data.joints2.data(), body, jointsDataSize2);
				body += jointsDataSize2;


				memcpy(data.vertices3.data(), body, verticesDataSize3);
				body += verticesDataSize3;

				memcpy(data.colors3.data(), body, colorsDataSize3);
				body += colorsDataSize3;

				memcpy(data.joints3.data(), body, jointsDataSize3);
				body += jointsDataSize3;


				memcpy(data.vertices4.data(), body, verticesDataSize4);
				body += verticesDataSize4;

				memcpy(data.colors4.data(), body, colorsDataSize4);
				body += colorsDataSize4;

				memcpy(data.joints4.data(), body, jointsDataSize4);
				body += jointsDataSize4;


				memcpy(data.vertices5.data(), body, verticesDataSize5);
				body += verticesDataSize5;

				memcpy(data.colors5.data(), body, colorsDataSize5);
				body += colorsDataSize5;

				memcpy(data.joints5.data(), body, jointsDataSize5);
				body += jointsDataSize5;


			}

			return true;
		}
		else {
			OFXSQUASHBUDDIES_WARNING << "Message Header doesn't match Mesh type";
			return false;
		}

	}

	//----------
	void Message::pushData(const void * data, size_t dataSize) {
		this->headerAndBody.append((const char *) data, dataSize);
	}

	//----------
	void * Message::getHeaderData() {
		return (void *) this->headerAndBody.data();
	}

	//----------
	const void * Message::getHeaderData() const {
		return (void *) this->headerAndBody.data();
	}

	//----------
	size_t Message::getHeaderSize() const {
		if (this->headerAndBody.size() > sizeof(Header::Basic)) {
			const auto & header = this->getHeader<Header::Basic>();
			return header.headerSize;
		}
		else {
			return 0;
		}
	}

	//----------
	void * Message::getBodyData() {
		return &this->headerAndBody[0] + this->getHeaderSize();
	}

	//----------
	const void * Message::getBodyData() const {
		return &this->headerAndBody[0] + this->getHeaderSize();
	}

	//----------
	size_t Message::getBodySize() const {
		return this->headerAndBody.size() - this->getHeaderSize();
	}

	//----------
	bool Message::empty() const {
		if (this->headerAndBody.empty()) {
			return true;
		}
		else if(this->headerAndBody.size() < this->getHeaderSize()) {
			return true;
		}
		else {
			return false;
		}
	}

	//----------
	void Message::resizeHeaderAndBody(size_t size) {
		this->headerAndBody.resize(size);
	}

	//----------
	const string & Message::getMessageString() const {
		return this->headerAndBody;
	}

	//----------
	size_t Header::MultiTrack_2_3_Frame::FrameSettings::size() const {
		return this->width * this->height * getBytesPerPixel(this->pixelFormat);
	}
}