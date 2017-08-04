built:
	g++ -o analysis analysis.cpp MyEventHits.C EventHits.C MyHits.C Hits.C Hit.cpp EventAnalysis.cpp `root-config --cflags --glibs`
