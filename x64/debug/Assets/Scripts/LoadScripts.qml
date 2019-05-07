import QtQuick 2.0

QtObject {
    Component.onCompleted: {
		//GlobalViewer.scene.globe.setTerrainProviderUrl('http://61.144.226.45:8084/Tile3D/B3DM/terrain');
		//GlobalViewer.scene.globe.setTerrainProviderUrl('http://61.144.226.45:8084/Tile3D/B3DM/terrain/mesh');
		//GlobalViewer.scene.globe.setTerrainProviderUrl('http://61.144.226.45:8084/Tile3D/B3DM/terra/longhua/terrainmesh');
		GlobalViewer.scene.globe.setTerrainProviderUrl('http://61.144.226.45:8088/terrain/mesh');
		
		if (false) {
			GlobalViewer.scene.globe.addImageryLayer({
				imageryProvider: {
					url: 'Assets/Textures/NaturalEarthII/{z}/{x}/{reverseY}.jpg',
					useWebMercator: false,
					tileWidth: 256,
					tileHeight: 256,
					minimumLevel: 0,
					maximumLevel: 2,
					hasAlphaChannel: false
				},
				minimumTerrainLevel: 0,
				maximumTerrainLevel: 100
			});
		} else {
			GlobalViewer.scene.globe.addArcGisMapServerImageryLayer({
				imageryProvider: {
					url: 'https://services.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer'
				},
				minimumTerrainLevel: 0,
				maximumTerrainLevel: 100
			});
		}
    }
}
