
// // //

std::istringstream headerStream;
std::istringstream dataStream;

std::string eventDelimiter = ";";

std::vector<int> eventContainer;

// // //

StatusCode DreamSiPMReader::open(const std::string inputFile) { // Any other necessary inputs?

  std::FILE *p_dataFile = std::fopen(inputFile, "rb");
  bool isFileOpenable = p_dataFile;

  if(!isFileOpenable) {
    dqm_error("The file at {0} could not be opened.", inputFile);
    throw StatusCodeException(STATUS_CODE_FAILURE);
  }

  std::string rawData;
  std::fseek(p_dataFile, 0, SEEK_END);
  rawData.resize(std::ftell(p_dataFile));
  std::rewind(p_dataFile);
  std::fread(&rawData[0], 1, rawData.size(), p_dataFile);
  std::fclose(p_dataFile);

  std::string headerTagOpen  = "<ACQUISITION_INFO>";
  std::string headerTagClose = "</ACQUISITION_INFO>";
  std::string dataTagStart   = "</START_NOTE>";

  int headerStartPos = rawData.find(headerTagOpen);
  int headerEndPos   = rawData.find(headerTagOpen) + headerTagOpen.size() - headerStartPos;
  int dataStartPos   = rawData.find(dataTagStart)  + dataTagStart.size();

  headerStream = rawData.substr(headerStart, headerEnd);
  dataSteam    = rawData.substr(dataStartPos);

  return STATUS_CODE_SUCCESS;
}

StatusCode DreamSiPMReader::skipNEvents(int nevents) {

  for (int e=0; e<nevents; e++) {
    std::string currentEventString;
    std::getline(dataStream, currentEventString);
    currentEventString.clear();
  }

  return STATUS_CODE_SUCCESS;
}

StatusCode DreamSiPMReader::runInfo(Run &runInfo) {

  // So what this needs to do is parse headerStream as XML, to extract the important information, then place it into the runInfo container.

  runInfo.setRunNumber();
  runInfo.setDetectorName();
  runInfo.setStartTime();
  // other run info:
  //   temperature
  //   datetime
  //   temperature2
  //   bias
  //   detector board
  //   detector model
  //   detector SN
  //   detector VOP
  //   acquisition board sn
  //   acquisition board RC
  //   board count
  //   board 1 id
  //   board 2 id
  // config info:
  //   trigger mode
  //   trigger level
  //   data delay 1
  //   trigger delay 1
  //   data delay 2
  //   trigger delay 2
  //   trigger hold
  //   polarity
  //   pileup rejector
  //   pileup time
  //   integration time
  //   baseline correction
  //   baseline constant
  //   noise filter
  //   digital gain
  //   correlated board

  return STATUS_CODE_SUCCESS;
}

StatusCode DreamSiPMReader::readNextEvent() {

  GenericEvent event;

  std::string currentEventString;
  std::getline(dataStream, currentEventString);

  if (currentEventString.size() <= 1) {
    dqm_warning("Event is blank");
    return STATUS_CODE_SUCCESS;
  }
  
  dqm4hep::core::tokenize(currentEventString, eventContainer, eventDelimiter);
  
  std::vector<float> ev_eventNum = {eventContainer[0]}
  event.setValues("Event", ev_eventNum);
  eventContainer.erase[0];

  std::vector<float> ev_time = {eventContainer[0]}
  event.setValues("Time", ev_time);
  eventContainer.erase[0];
  
  if (eventContainer.size() == 64) {
    event.setValues("Channels", eventContainer);
  }
  else {
    dqm_error("Event {0} : wrong number of members", ev_eventNum[0]);
    throw StatusCodeException(STATUS_CODE_FAILURE);
  }

  onEventRead().emit(event); // Do we need to use the pointer, or can we just put in the event itself?
  return STATUS_CODE_SUCCESS;
}

StatusCode DreamSiPMReader::close() {

  // We already close the file in DreamSiPMReader::open(), so we don't need to close it here.
  // Moreover, we *can't* really close it here anyway, since it will go out of scope once open() returns.

  // So what do we need to do here, if anything?

  return STATUS_CODE_SUCCESS;
}
