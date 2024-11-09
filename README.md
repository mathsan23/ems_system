# Learn C
Scripts developed during C classes of the USP Specialization in Aeronautical Systems


## EMS System

The Event Manager System (EMS) is the system responsible for receiving asynchronous event requests from several other sub-systems in the aircraft, prioritizing them and handing them over to the appropriate event handling system (EHS)

1. The Events received by the EMS must have the following properties:
- Event Description
- Request Time
- Event Priority

2. The system must hand over the events to the event handling system (EHS) according to the following rules:
- High priority events must be handed over before Normal priority events
- When events have the same priority, older events must be handed over before more recent events

3. After a successful event handover, the EMS must delete the event from its memory. An event handover is
considered successful if the EMS receives the ACK message from the EHS.

4. In case the event hand over is not successful, the EMS must maintain the event in memory.

 - The ACK message is composed by a single boolean. False means that the event was not received properly by the EHS, while True means a successful hand over of the event.