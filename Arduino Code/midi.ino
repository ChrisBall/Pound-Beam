void midiUpdate() {
  currentMidiNote = sm.getScaleNote(outputScaleNote);
  if (notePlaying) { //if trigger input is 'on'
    if (currentMidiNote != activeMidiNote) {
      midiNoteOff(0, activeMidiNote, midiVolume); //turn off last note
      midiNoteOn(0, currentMidiNote, midiVolume); //turn on last note
      activeMidiNote = currentMidiNote;
    }
  } else {
    if (activeMidiNote != 128) {
      midiNoteOff(0, activeMidiNote, midiVolume); //turn off last note
      activeMidiNote = 128;
    }
  }
}

void midiSetInstrument(uint8_t chan, uint8_t inst) {
  if (chan > 15) return;
  inst --; // page 32 has instruments starting with 1 not 0 :(
  if (inst > 127) return;

  VS1053.write(MIDI_CHAN_PROGRAM | chan);
  VS1053.write(inst);
}


void midiSetChannelVolume(uint8_t chan, uint8_t vol) {
  if (chan > 15) return;
  if (vol > 127) return;

  VS1053.write(MIDI_CHAN_MSG | chan);
  VS1053.write(MIDI_CHAN_VOLUME);
  VS1053.write(vol);
}

void midiSetChannelBank(uint8_t chan, uint8_t bank) {
  if (chan > 15) return;
  if (bank > 127) return;

  VS1053.write(MIDI_CHAN_MSG | chan);
  VS1053.write((uint8_t)MIDI_CHAN_BANK);
  VS1053.write(bank);
}

void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel) {
  if (chan > 15) return;
  if (n > 127) return;
  if (vel > 127) return;

  VS1053.write(MIDI_NOTE_ON | chan);
  VS1053.write(n);
  VS1053.write(vel);

  if(MIDIMODE){
    Serial.write(MIDI_NOTE_ON | chan);
    Serial.write(n);
    Serial.write(vel);
  }
}

void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel) {
  if (chan > 15) return;
  if (n > 127) return;
  if (vel > 127) return;

  VS1053.write(MIDI_NOTE_OFF | chan);
  VS1053.write(n);
  VS1053.write(vel);

  if(MIDIMODE){
    Serial.write(MIDI_NOTE_OFF | chan);
    Serial.write(n);
    Serial.write(vel);
  }
}
