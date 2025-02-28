class ToggleCabinet {
    constructor() {
      this.values = {
        sectorOneOn: true,
        sectorTwoOn: true,
        sectorThreeOn: true,
        sectorFourOn: true,
        sectorFiveOn: true,
        sectorSixOn: true,
        sectorSevenOn: true,
        sectorEightOn: true,
        turnedOnCount: 0,
        cabinetOn: true,
        isLocked: false,
      };
    }
  
    swapValue(key) {
      if (this.values.hasOwnProperty(key)) {
        this.values[key] = !this.values[key];
      }
      this.countTurnedOn();
    }
  
    getValue(key) {
      return this.values[key];
    }

    countTurnedOn() {
      let turnedCount = 0;
      if (this.values['sectorOneOn']) turnedCount += 1;
      if (this.values['sectorTwoOn']) turnedCount += 1;
      if (this.values['sectorThreeOn']) turnedCount += 1;
      if (this.values['sectorFourOn']) turnedCount += 1;
      if (this.values['sectorFiveOn']) turnedCount += 1;
      if (this.values['sectorSixOn']) turnedCount += 1;
      if (this.values['sectorSevenOn']) turnedCount += 1;
      if (this.values['sectorEightOn']) turnedCount += 1;

      this.values['turnedOnCount'] = turnedCount;
      if (this.values['turnedOnCount']  === 0) {
        this.values['cabinetOn'] = false;
      } else {
        this.values['cabinetOn'] = true;
      }
    }

    turnState() {
      this.values['cabinetOn'] = !this.values['cabinetOn'];
      if (this.values['cabinetOn'] &&
          !this.values['sectorOneOn'] && !this.values['sectorTwoOn'] &&
          !this.values['sectorThreeOn'] && !this.values['sectorFourOn'] &&
          !this.values['sectorFiveOn'] && !this.values['sectorSixOn'] &&
          !this.values['sectorSevenOn'] && !this.values['sectorEightOn']
      ) {
        this.values['sectorOneOn'] = true;
        this.values['sectorTwoOn'] = true;
        this.values['sectorThreeOn'] = true;
        this.values['sectorFourOn'] = true;
        this.values['sectorFiveOn'] = true;
        this.values['sectorSixOn'] = true;
        this.values['sectorSevenOn'] = true;
        this.values['sectorEightOn'] = true;
      }

      if (this.values['cabinetOn']) {
        this.values['isLocked'] = false;
      } else {
        this.values['isLocked'] = true;
      }
    }
  }
  
  const toggleCabinet = new ToggleCabinet();
  export default toggleCabinet;