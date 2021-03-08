#include "Stack.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


void testMakeAStack(){
	Stack *s = makeStack();
	int freshStackHasZeroElements = countStack(s);
	destroyStack(s);
	ASSERT_EQUAL(0,freshStackHasZeroElements);
}

void testPushOne(){
	Stack *s=makeStack();
	pushStack(s,1);
	int onePushStackHasOneElement = countStack(s);
	destroyStack(s);
	ASSERT_EQUAL(1,onePushStackHasOneElement);
}

void testPushTopOne(){
	Stack *s=makeStack();
	pushStack(s,42);
	int topAfterPush = topOfStack(s);
	destroyStack(s);
	ASSERT_EQUAL(42,topAfterPush);
}

void testPushPopEmpty(){
	Stack *s=makeStack();
	pushStack(s,42);
	int topval=topOfStack(s);
	popStack(s);
	int szafterpop = countStack(s);
	destroyStack(s);
	ASSERT_EQUAL(42,topval);
	ASSERT_EQUAL(0,szafterpop);
}





bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testMakeAStack));
	s.push_back(CUTE(testPushOne));
	s.push_back(CUTE(testPushTopOne));
	s.push_back(CUTE(testPushPopEmpty));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
