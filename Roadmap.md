# Milestone roadmap (≈ 12–14 weeks @ ~5 hr/wk)
### Week 1 - Project skeleton & repo
- Create a GitHub repo with three folders: /hardware, /firmware, /models.
- Add a one-page Project Charter (problem, scope, success criteria, risks).
- Wire ESP32 → one relay + one LED; commit a “hello hardware” with PlatformIO/Arduino.

### Week 2 – Power, safety, measurement
- Assemble 12 V supply with fuse + E-stop + distribution bus.
- Test limit switch control with ISR and semaphore
 - Solder two limit switches
 - Create an LED toggle
 - Create forward and reverse logic and limit switch stops for a servo
- Breadboard INA219 reading feeder current; print to serial + LCD.

### Week 3 – First visible switch
- CAD & 3D-print a servo mount + knife-switch lookalike (simple, sturdy). Add two limit switches.
 -ESP32: servo open/close with debounced limit-switch feedback + timeout fault.
- Document: BOM v0 and wiring diagram.

### Week 4 – Fault module v1
- Build fault path with power resistor + high-current toggle or MOSFET + heatsink.
- Implement overcurrent pickup and a simple instantaneous trip on Segment A.
- Add a status LED stack (healthy/pickup/trip).

### Week 5 – Main breaker + reclose 1-shot
- Add “main breaker” as a relay channel with trip/close.
- Implement 1-shot reclose logic (trip → 0.5 s dead-time → reclose).
- Add event logging (serial and CSV line over UART).

### Week 6 – Full 3-shot recloser
- Implement 3-shot profile (Fast-Fast-Delayed). Tune delays as constants.
- Add LCD HMI: show Feeder state, shot count, last fault current.
- Unit-test state machine with simulated currents (software test mode).

### Week 7 – Sectionalizer module
- Build a passive sectionalizer panel (servo + limit switches) that opens only during dead time if it counted N upstream trips.
- Write logic: count lockout events, arm to open on the next dead interval; re-energize afterwards.

### Week 8 – Capacitor bank module
- Build a small cap bank (safe electrolytics w/ limiting resistor + discharge resistor).
- Control via relay; inrush delay + minimum on/off time; simple “VAr” simulator variable in firmware.

### Week 9 – Tie/transfer bus
- Add a tie switch module. Implement logic to backfeed if source side is down and tie is commanded closed.
- Add interlocks to prevent closing into fault/lockout.

### Week 10 – Refactor & documentation sprint
- Refactor firmware into /core (FSM), /io (drivers), /ui, /sim.
- Create README diagrams (block + state charts). Photograph your panels and add wiring drawings.
- GitHub Issues: create tasks for polish/bugs.

### Week 11 – Validation tests
- Define a Test Matrix: normal close, load step, fault A with 1-shot clear, persistent fault lockout, sectionalizer isolation, cap switching, tie backfeed.
- Record current/time graphs (print to CSV; plot in a notebook if you like).

### Week 12 – Demo build & report
- Cable-manage, label, add panel overlays (printed legends).
- Final Demo Script: show normal ops → apply fault → reclose sequence → sectionalize → restore.

# Write a 2–3 page Tech Note (how it works, what’s simulated vs real, results, future work).
- Stretch (Weeks 13–14)
- ESP-NOW or MQTT to a laptop dashboard.

MicroSD event log with timestamps (add RTC or NTP).

Simple one-line “SCADA” screen in a web UI.
