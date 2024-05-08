#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_12.8.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestAppend)
		{
			// Arrange
			Node* head = nullptr;

			// Act
			append(head, 5);

			// Assert
			Assert::IsNotNull(head);
			Assert::AreEqual(head->data, 5);
			Assert::AreEqual(head->next->data, 5); 
			Assert::AreEqual(head->prev->data, 5); 

			
			delete head;
		}

		TEST_METHOD(TestInsertAtPosition)
		{
			// Arrange
			Node* head = nullptr;
			append(head, 1);
			append(head, 2);
			append(head, 3);

			// Act
			insertAtPosition(head, 3, 3);

			// Assert
			Assert::AreEqual(head->next->next->data, 3);
			Assert::AreEqual(head->next->next->next->data, 3);

			
			delete head;
		}

		TEST_METHOD(TestDeleteHead)
		{
			// Arrange
			Node* head = nullptr;
			append(head, 1);
			append(head, 2);
			append(head, 3);

			// Act
			deleteHead(head);

			// Assert
			Assert::AreEqual(head->data, 2);
			Assert::AreEqual(head->prev->data, 3);
			Assert::AreEqual(head->next->data, 3);

			
			delete head;
		}
	};
}
