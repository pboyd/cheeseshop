CXXFLAGS=-Itoml

cheeseshop: cheeseshop.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
