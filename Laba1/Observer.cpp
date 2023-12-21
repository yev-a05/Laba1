#include <iostream>
#include <vector>
#include <algorithm>

// Абстрактный подписчик
class Subscriber {
public:
	virtual void update(const std::string& message) = 0;
};

// Абстрактный издатель
class Publisher {
protected:
	std::vector<Subscriber*> subscribers;

public:
	void subscribe(Subscriber* subscriber) {
		subscribers.push_back(subscriber);
	}

	int getSubscriberCount() const {
		return subscribers.size();
	}

	void unsubscribe(Subscriber* subscriber) {
		std::vector<Subscriber*>::iterator it = std::find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end()) {
			subscribers.erase(it);
		}
	}

	void notify(const std::string& message) {
		for (std::vector<Subscriber*>::iterator it = subscribers.begin(); it != subscribers.end(); ++it) {
			(*it)->update(message);
		}
	}
};

class LoggingListener : public Subscriber {
public:
	void update(const std::string& message) override {
		std::cout << "Получено сообщение (лог): " << message << std::endl;
	}
};

class EmailAlertsListener : public Subscriber {
public:
	void update(const std::string& message) override {
		std::cout << "Получено сообщение (электронная почта): " << message << std::endl;
	}
};

class Editor {
private:
	std::string File;
	Publisher* events; // Указатель на Publisher

public:
	Editor() {
		events = new Publisher();
	}

	~Editor() {
		delete events;
	}

	void openFile(const std::string& path) {
		File = path;
		events->notify("Open file: " + File);
	}

	void saveFile(const std::string& path) {
		File = path;
		events->notify("Save file: " + File);
	}

	void subscribe(Subscriber* subscriber) {
		events->subscribe(subscriber);
	}

	void unsubscribe(Subscriber* subscriber) {
		events->unsubscribe(subscriber);
	}
};

int main() {
	Editor editor;
	LoggingListener listener1;
	EmailAlertsListener listener2;

	editor.subscribe(&listener1);
	editor.subscribe(&listener2);

	editor.openFile("file.txt");
	editor.saveFile("newfile.txt");

	return 0;
}