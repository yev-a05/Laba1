#include "pch.h"
#include "CppUnitTest.h"
#include "..\Laba1\Observer.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SubscriberTest)
	{
	public:
		TEST_METHOD(TestLoggingListenerUpdate)
		{
			LoggingListener listener;
			std::stringstream output;
			std::streambuf* prevOut = std::cout.rdbuf(output.rdbuf());

			listener.update("Test message");

			std::cout.rdbuf(prevOut);

			Assert::AreEqual("Получено сообщение (лог): Test message\n", output.str().c_str());
		}

		TEST_METHOD(TestEmailAlertsListenerUpdate)
		{
			EmailAlertsListener listener;
			std::stringstream output;
			std::streambuf* prevOut = std::cout.rdbuf(output.rdbuf());

			listener.update("Test message");

			std::cout.rdbuf(prevOut);

			Assert::AreEqual("Получено сообщение (электронная почта): Test message\n", output.str().c_str());
		}
	};

	TEST_CLASS(PublisherTest)
	{
	public:
		TEST_METHOD(TestPublisherSubscribe)
		{
			Publisher publisher;
			LoggingListener listener;

			publisher.subscribe(&listener);

			Assert::IsTrue(publisher.getSubscriberCount() == 1);
		}

		TEST_METHOD(TestPublisherUnsubscribe)
		{
			Publisher publisher;
			LoggingListener listener;

			publisher.subscribe(&listener);
			publisher.unsubscribe(&listener);

			Assert::IsTrue(publisher.getSubscriberCount() == 0);
		}

		TEST_METHOD(TestPublisherNotify)
		{
			Publisher publisher;
			LoggingListener listener;
			std::stringstream output;
			std::streambuf* prevOut = std::cout.rdbuf(output.rdbuf());

			publisher.subscribe(&listener);
			publisher.notify("Test message");

			std::cout.rdbuf(prevOut);

			Assert::AreEqual("Получено сообщение (лог): Test message\n", output.str().c_str());
		}
	};

	TEST_CLASS(EditorTest)
	{
	public:
		TEST_METHOD(TestEditorOpenFile)
		{
			Editor editor;
			LoggingListener listener;
			std::stringstream output;
			std::streambuf* prevOut = std::cout.rdbuf(output.rdbuf());

			editor.subscribe(&listener);
			editor.openFile("file.txt");

			std::cout.rdbuf(prevOut);

			Assert::AreEqual("Получено сообщение (лог): Open file: file.txt\n", output.str().c_str());
		}

		TEST_METHOD(TestEditorSaveFile)
		{
			Editor editor;
			LoggingListener listener;
			std::stringstream output;
			std::streambuf* prevOut = std::cout.rdbuf(output.rdbuf());

			editor.subscribe(&listener);
			editor.saveFile("newfile.txt");

			std::cout.rdbuf(prevOut);

			Assert::AreEqual("Получено сообщение (лог): Save file: newfile.txt\n", output.str().c_str());
		}
	};
}
